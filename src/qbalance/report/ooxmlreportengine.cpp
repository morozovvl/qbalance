/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/
#include <QtCore/QFileInfo>
#include <QtCore/QTemporaryFile>
#include <QtCore/QTimer>
#include <QtCore/QProcess>
#include <QtCore/QDebug>
#include "ooxmlreportengine.h"
#include "../openoffice/ooxmlengine.h"
#include "../engine/documentscriptengine.h"
#include "../engine/reportcontext.h"
#include "../kernel/app.h"
#include "../gui/tableview.h"


OOXMLReportEngine::OOXMLReportEngine(Essence* ess, DocumentScriptEngine* engine) : ReportEngine(engine)
{
    app = TApplication::exemplar();
    essence = ess;
    ooxmlEngine = new OOXMLEngine();
    ooPath = "";
    tableNameForPrinting = "";
    fileName = "";
}


OOXMLReportEngine::~OOXMLReportEngine()
{
    delete ooxmlEngine;
}


bool OOXMLReportEngine::open()
{
    return ReportEngine::open();
}


void OOXMLReportEngine::setFileName(QString fName)
{
    fileName = fName;
}


bool OOXMLReportEngine::open(QString fileName, ReportContext* cont, bool justPrint, int copyCount, QString printerName)
{
    int strNumber = 0;
    if (ooxmlEngine->open(fileName))
    {
        context = cont;
        QString barCodePicture = findBarCode();
        if (barCodePicture.size() > 0)     // Найден штрих-код
        {
            strNumber = essence->getGrdTable()->currentIndex().row() + 1;      // Будем печатать одну конкретную текущую строку
            context->setCurrentRow(strNumber);
            QProcess* zint = new QProcess();
            zint->setWorkingDirectory(ooxmlEngine->getTmpDir());
            QString zintCommandLine = "zint -o " + barCodePicture;
            zintCommandLine.append(QString(" -b %1").arg(app->getConfigValue("BAR_CODE_PRINTER_BARCODETYPE").toInt()));
            zintCommandLine.append(QString(" --height=%1").arg(app->getConfigValue("BAR_CODE_PRINTER_BARCODEHEIGHT").toInt()));
            zintCommandLine.append(" --border=0");
            zintCommandLine.append(" -d " + essence->prepareBarCodeData());
#if defined(Q_OS_LINUX)
                zint->start(zintCommandLine);
#elif defined(Q_OS_WIN)
                zint->start(app->applicationDirPath() + zintCommandLine);
#endif
            if (app->waitProcessEnd(zint))
            {

            }
            else
            {
                app->showError(QObject::trUtf8("Не удалось запустить программу") + " zint");
                return false;
            }

        }
        findTables();
        foreach (QString table, tablesForPrinting)
        {
            tableNameForPrinting = table;
            writeVariables(strNumber);       // Перепишем переменные из контекста печати в файл content.xml
        }

        if (scriptEngine != 0)
            scriptEngine->eventBeforeTotalPrint();

        writeHeader();

        if (justPrint && copyCount > 1)     // Если будем печатать сразу несколько копий
            copyPage(copyCount);            // То страницу размножим

        ooxmlEngine->close();

        // Запустим OpenOffice
        if (ooPath.size() == 0)
        {
            ooPath = app->getConfigValue("OO_PATH").toString();
#if defined(Q_OS_LINUX)
//            ooPath = TApplication::exemplar()->findFileFromEnv("soffice");
            if (ooPath.size() > 0)
                ooPath = ooPath.append("/");
            ooPath += "soffice";
#elif defined(Q_OS_WIN)
//            ooPath = TApplication::exemplar()->findFileFromEnv("soffice.exe");
            if (ooPath.size() > 0)
                ooPath = ooPath.append("\\");
            ooPath += "soffice.exe";
#endif
        }
        QProcess* ooProcess = new QProcess();
        QStringList commandLine;
        commandLine << "--calc" << "--invisible" << "--quickstart";
        if (justPrint && printerName.size() > 0)
            commandLine << "--pt" << printerName;
        commandLine << fileName;
        ooProcess->start(ooPath, commandLine);
        if (!ooProcess->waitForStarted())    // Подождем 1 секунду и если процесс не запустился
            TApplication::exemplar()->showError(QObject::trUtf8("Не удалось запустить") + " Open Office" + ". " + ooProcess->errorString());                  // выдадим сообщение об ошибке
        else
            return true;
    }
    return false;
}


void OOXMLReportEngine::writeVariables(int strNumber)
/*
Ищет в шаблоне content.xml (см.разархивированный файл OpenOffice) ячейки с текстом вида "[<выражение>]".
Заменяет <выражение> значением из контекста печати. Для этого:
1. "Ищет" тело табличной части и заполняет ее данными.
    Шаблоном строки таблицы является первая строка тела таблицы в шаблоне документа.
    Если в теле таблицы несколько строк, то из первой строки клонируются новые строки
    Попутно создается список выражений, которые нужно пропустить через скриптовый движок
*/
{
    QDomDocument* doc = ooxmlEngine->getDomDocument();

    expressionsForEvaluation.clear();           // очистим список выражений для скриптового движка

// Пункт 1 (см. комментарий выше)

    cells = doc->elementsByTagName("text:p");   // будем выбирать только те ячейки, которые содержат текст
    // Найдем первую ячейку тела таблицы
    QDomNode firstRowNode;      //  в этой переменной будет ссылка на первую ячейку таблицы

    // просмотрим все текстовые ячейки, найдем ту, в которой начинается "тело" таблицы
    for (int i = 0; i < cells.count() && firstRowNode.isNull(); i++)
    {
        if (getTableVariable(cells.at(i).toElement(), tableNameForPrinting).size() > 0)   // если ячейка таблицы OpenOffice содержит выражение "[таблица<...>]"
        {
            firstRowNode = cells.at(i).parentNode().parentNode();   // то значит в этой ячейке начинается табличная часть документа ("тело" таблицы, не шапка)
            break;                                                  // закончим поиск
        }
    }

    if (!firstRowNode.isNull())                 // Если в шаблоне было найдено "тело" таблицы
    {
        QDomNode lastNode = firstRowNode;       // lastNode будет указывать на последнюю добавленную строку таблицы
        int strNum = 1;
        int strCounter = scriptEngine->getReportContext()->getRowCount(tableNameForPrinting);
        if (strNumber > 0)          // Это ценник со штрих-кодом
        {
            strNum = strNumber;     // Будем печатать только одну строку
            strCounter = strNum;
        }
        for (; strNum <= strCounter; strNum++)    // по порядку строк документа
        {
            if (scriptEngine->eventBeforeLinePrint(strNum))
            {
                QDomNode clone = firstRowNode.cloneNode();              // склонируем первую строку тела таблицы, будем читать из и писать в клон строки
                cells = clone.toElement().elementsByTagName("text:p");  // создадим список ячеек первой строки тела таблицы (узлов XML)
                for (int i = 0; i < cells.count(); i++)     // будем по порядку просматривать этот список, пока есть что смотреть
                {
                    readExpression(i, strNum);                     // будем читать выражение в ячейке, искать для него данные в контексте печати и записывать эти данные в ячейку
                }
                lastNode = firstRowNode.parentNode().insertAfter(clone, lastNode);  // то добавим клон строки после первой строки тела документа
            }

            scriptEngine->eventAfterLinePrint(strNum);

        }
        firstRowNode.parentNode().removeChild(firstRowNode);                        // удалим первую строку тела документа, т.к. в ней содержатся только шаблоны (без данных)
                                                                                    // он не заполнялся данными, т.к. был нужен для клонирования следующих строк
    }
}


void OOXMLReportEngine::writeHeader()
/*
2.  Заполняет данными оставшиеся в документе ячейки, содержащие шаблон "[<выражение>]", не входящие в тело таблицы.
    Попутно создается список выражений, которые нужно пропустить через скриптовый движок
3.  Подготовленный список выражений пропускается через скриптовый движок и результаты записываются в соответствующие ячейки документа
*/
{
    QDomDocument* doc = ooxmlEngine->getDomDocument();
    expressionsForEvaluation.clear();           // очистим список выражений для скриптового движка
    cells = doc->elementsByTagName("text:p");   // будем выбирать только те ячейки, которые содержат текст
    tableNameForPrinting = context->getTableName();

// Пункт 2 (см. комментарий выше)

    // Теперь вставим все оставшиеся переменные
    cells =  doc->elementsByTagName("text:p");  // будем выбирать только те ячейки, которые содержат текст
    bool valFound = false;
    while (!valFound)
    {
        valFound = true;
        int i = 0;
        for (; i < cells.count(); i++)
        {
            readExpression(i);
        }
        i = 0;
        for (; i < cells.count(); i++)
        {
            readExpression(i, 1);
        }
    }


// Пункт 3 (см. комментарий выше)
    // Теперь пропустим документ через скрипты, чтобы вычислить выражения
    cells =  doc->elementsByTagName("text:p");    // будем выбирать только те ячейки, которые содержат текст
    for (int i = 0; i < cells.count(); i++)      // просмотрим все ячейки
    {
        QString cellText = cells.at(i).toElement().text().trimmed();        // Получим текст текущей ячейки
        if (expressionsForEvaluation.contains(cellText))                    // Если значение ячейки находится в списке
        {
            QVariant var = scriptEngine->evaluate(cellText).toVariant();    // то оценим его скриптовым движком
            if (!scriptEngine->hasUncaughtException())                      // и если не было ошибок...
                writeCell(cells.at(i), cellText, var);                      // запишем результат оценки вместо текста ячейки
        }
    }
}


bool OOXMLReportEngine::readExpression(int i, int strNum)
/*
Обрабатывает одну ячейку. Оценивает выражение в ячейке. Определяет, относится ли выражение к телу таблицы.
Получает данные для выражения из контекста печати. Записывает эти данные в XML модель документа.
i - номер ячейки в списке элементов, подлежащих рассмотрению вообще
strNum - номер текущей строки тела таблицы
*/
{
    bool result = true;         // результат оценки выражения
    QRegExp rx("\\[.+\\]");     // фильтр (регулярное выражение) для отсеивания не нужных символов в шаблоне
    while(true)                 // бесконечный цикл, чтобы в выражении можно было бы обработать любое количество элементов "[<...>]"
                                // что позволяет строить сложные выражения
    {
        QString cellText = cells.at(i).toElement().text().trimmed();    // получим текст выражения в ячейке, которую мы обрабатываем
        int fpos = cellText.indexOf(rx, 0);     // найдем позицию, с которой начинается шаблон "[<...>]"
        if (fpos >= 0)                          // если шаблон найден
        {
            QVariant var;
            QString value;
            // Ячейка относится к таблице
            int lpos = cellText.indexOf("]", fpos) + 1;
            value = cellText.mid(fpos, lpos - fpos);
            value = value.remove("[").remove("]");      // освободим его от квадратных скобок
            if (strNum > 0)
                var = context->getValue(value, strNum);
            else
                var = context->getValue(value);

            if (var.isValid())
                writeCell(cells.at(i), "[" + value + "]", var);
            else
                break;
        }
        else
        {
            result = false;
            break;  // элементов "[<...>]" в выражении больше нет, выходим
        }
    }
    return result;
}


QString OOXMLReportEngine::getTableVariable(QDomElement cell, QString tableName)
// Если ячейка таблицы OpenOffice содержит выражение "[таблица<...>]", то возвращает это выражение.
// Иначе возвращается пустая строка
{
    QRegExp rx("\\[.+\\]");                                 // фильтр (регулярное выражение) для отсеивания нужных ячеек в шаблоне
    int fpos = 0;           // позиция начала выражения "[<...>]"
    int lpos = 0;           // позиция конца выражения  "[<...>]"

    // преобразуем очередную ячейку в текстовую строку
    QString cellText = cell.text().trimmed();

    // если в этой строке (т.е. в текущей ячейке OpenOffice) имеется выражение, похожее на наш фильтр "[<выражение>]"
    fpos = cellText.indexOf(rx, 0);
    if (fpos >= 0)
    {                                                       // в позиции fpos в строке начинается выражение "[<...>]"
        lpos = cellText.indexOf("]", fpos) + 1;             // в позиции lpos оно заканчивается
        QString svar = cellText.mid(fpos, lpos - fpos);             // svar содержит выражение вместе с квадратными скобками
        QString dvar = QString(svar).remove("[").remove("]");       //dvar содержит выражение без квадратных скобок, в чистом виде
        if (dvar.left(tableNameForPrinting.size()).toLower() == tableName)                    // Если выражение начинается со слова "таблица" (т.е. "[таблица<...>]")
        {
            return dvar;   // то значит в этой ячейке начинается табличная часть документа (тело таблицы, не шапка)
        }
    }
    return "";
}


bool OOXMLReportEngine::writeCell(QDomNode n, QString svar, QVariant var)
//  Записывает в узел n XML модели документа значение var вместо выражения svar
{
    bool result = true;
    if (!var.isValid() || var.isNull())
    {
        result = false;
    }

    QString cellText = n.toElement().text().trimmed();
    QString type = "string";        // тип записываемого значения с точки зрения OpenOffice
    QString valueString;

    // Определим тип записываемого значения, преобразуем его в строку
    if ((var.type() == QVariant::Double) ||
        (var.type() == QVariant::Int) ||
        (var.type() == QVariant::UInt))
    {
        valueString = var.toString();                           // это числовое значение
        type = "float";                                         // в OpenOffice оно имеет тип "float"
    }
    else if (var.type() == QVariant::DateTime)
    {
        valueString = var.toDateTime().toString("dd.MM.yyyy hh:mm:ss");
    }
    else if (var.type() == QVariant::Date)
    {
        valueString = var.toDate().toString(app->dateFormat());
    }
    else
    {
        valueString = var.toString().trimmed();
    }

    // Заменим в ячейке выражение svar на строковый аналог значения var
    if (svar.size() > 0)
        cellText.replace(svar, valueString);

    // Если замена произошла не полностью и больше в выражении нет шаблонов "[<...>]"
    if (cellText != valueString && cellText.indexOf("[", 0) == -1) // то возможно в ячейке имеется скриптовое выражение
    {
        if (!expressionsForEvaluation.contains(cellText))           // если это скриптовое выражение не встречалось нам раньше
        {
            expressionsForEvaluation.append(cellText);              // то запишем его в список и позднее пропустим выражение через скриптовый движок
            type = "string";                                        // и запишем его в модель XML как текстровое выражение
        }
    }
    ooxmlEngine->writeCell(n, cellText, type);
    return result;
}


void OOXMLReportEngine::findTables()
{
    QRegExp rx("^\\D+\\d+\\..+$");
    QRegExp rm("\\d+\\..+$");
    tablesForPrinting.clear();
    foreach (QString key, context->getData()->keys())
    {
        if (key.contains(rx))
        {
            QString table = key.remove(rm);
            if (!tablesForPrinting.contains(table))
                tablesForPrinting.append(table);
        }
    }
}


QString OOXMLReportEngine::findBarCode()
{
    QString result = "";
    QDomDocument* doc = ooxmlEngine->getDomDocument();

// Обработка штрих-кодов
    cells =  doc->elementsByTagName("draw:frame");    // Просмотрим все фреймы для картинок
    for (int i = 0; i < cells.count(); i++)      // просмотрим все ячейки
    {
        if (cells.at(i).toElement().attribute("draw:name") == "BarCode")
        {
            result = cells.at(i).firstChildElement("draw:image").attribute("xlink:href");
            break;
        }
    }
    return result;
}


void OOXMLReportEngine::copyPage(int copyCount)
{
    QDomDocument* doc = ooxmlEngine->getDomDocument();
    QDomNode firstNode = doc->elementsByTagName("office:spreadsheet").at(0);
    QDomNode lastNode = firstNode;
    for (int i = 1; i < copyCount; i++)     // будем по порядку просматривать этот список, пока есть что смотреть
    {
        QDomNode clone = firstNode.cloneNode();              // склонируем первую строку тела таблицы, будем читать из и писать в клон строки
        lastNode = firstNode.parentNode().insertAfter(clone, lastNode);  // то добавим клон строки после первой строки тела документа
    }
}
