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
#include <QDebug>
#include "ooxmlreportengine.h"


OOXMLReportEngine::OOXMLReportEngine(ReportScriptEngine* engine) : ReportEngine(engine)
{
    ooxmlEngine = new OOXMLEngine();
}


OOXMLReportEngine::~OOXMLReportEngine()
{
    delete ooxmlEngine;
}


bool OOXMLReportEngine::open(QString fileName, QMap<QString, QVariant>* cont)
{
    if (ooxmlEngine->open(fileName))
    {
        context = cont;
        writeVariables();       // Перепишем переменные из контекста печати в файл content.xml
        ooxmlEngine->close();

        // Запустим OpenOffice
        QProcess* ooProcess = new QProcess();
        ooProcess->start("soffice", QStringList() << "--invisible" << "--quickstart" << fileName);

        if ((!ooProcess->waitForStarted(1000)) && (ooProcess->state() == QProcess::NotRunning))    // Подождем 1 секунду и если процесс не запустился
            TApplication::exemplar()->showError(QObject::trUtf8("Не удалось запустить") + " Open Office");                  // выдадим сообщение об ошибке
        else
            return true;
    }
    return false;
}


void OOXMLReportEngine::writeVariables()
/*
Ищет в шаблоне content.xml (см.разархивированный файл OpenOffice) ячейки с текстом вида "[<выражение>]".
Заменяет <выражение> значением из контекста печати. Для этого:
1. "Ищет" тело табличной части и заполняет ее данными.
    Шаблоном строки таблицы является первая строка тела таблицы в шаблоне документа.
    Если в теле таблицы несколько строк, то из первой строки клонируются новые строки
    Попутно создается список выражений, которые нужно пропустить через скриптовый движок
2.  Заполняет данными оставшиеся в документе ячейки, содержащие шаблон "[<выражение>]", не входящие в тело таблицы.
    Попутно создается список выражений, которые нужно пропустить через скриптовый движок
3.  Подготовленный список выражений пропускается через скриптовый движок и результаты записываются в соответствующие ячейки документа
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
        if (getTableVariable(cells.at(i).toElement()).size() > 0)   // если ячейка таблицы OpenOffice содержит выражение "[таблица<...>]"
        {
            firstRowNode = cells.at(i).parentNode().parentNode();   // то значит в этой ячейке начинается табличная часть документа ("тело" таблицы, не шапка)
            break;                                                  // закончим поиск
        }
    }

    if (!firstRowNode.isNull())                 // Если в шаблоне было найдено "тело" таблицы
    {
        QDomNode lastNode = firstRowNode;       // lastNode будет указывать на последнюю добавленную строку таблицы
        bool valFound = true;                   // флаг, указывающий, что заполнение таблицы нужно закончить
        for (int strNum = 1; valFound; strNum++)    // по порядку строк документа
        {
            QDomNode clone = firstRowNode.cloneNode();              // склонируем первую строку тела таблицы, будем читать из и писать в клон строки
            cells = clone.toElement().elementsByTagName("text:p");  // создадим список ячеек первой строки тела таблицы (узлов XML)
            for (int i = 0; i < cells.count() && valFound; i++)     // будем по порядку просматривать этот список, пока есть что смотреть
            {
                if (!readExpression(i, strNum))                     // будем читать выражение в ячейке, искать для него данные в контексте печати и записывать эти данные в ячейку
                {
                    valFound = false;                               // больше искать нечего
                    break;                                          // выходим из цикла
                }
            }
            if (valFound)                                                           // если для строки найдены все данные
                lastNode = firstRowNode.parentNode().insertAfter(clone, lastNode);  // то добавим клон строки после первой строки тела документа
        }
        firstRowNode.parentNode().removeChild(firstRowNode);                        // удалим первую строку тела документа, т.к. в ней содержатся только шаблоны (без данных)
                                                                                    // он не заполнялся данными, т.к. был нужен для клонирования следующих строк
    }


// Пункт 2 (см. комментарий выше)

    // Теперь вставим все оставшиеся переменные
    cells =  doc->elementsByTagName("text:p");  // будем выбирать только те ячейки, которые содержат текст
    for (int i = 0; i < cells.count(); i++)
    {
        readExpression(i, 1);             // будем читать выражение в ячейке, искать для него данные в контексте печати и записывать эти данные в ячейку
                                          // данные для выражений, которые выглядят как [<таблица...>] и находятся вне тела таблицы, будут браться из первой строки тела таблицы
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
            {
                writeCell(cells.at(i), cellText, var);                      // запишем результат оценки вместо текста ячейки
            }
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
            QString value = getTableVariable(cells.at(i).toElement());  // проверим, не ячейка ли это тела таблицы
            if (value.size() > 0)           // если ячейка таблицы OpenOffice содержит выражение "[таблица<...>]"
            {
                QString sval = value;       // если это тело таблицы, то из контекста печати получим данные для соответствующей строки таблицы для этого выражения
                var = context->value(sval.replace("таблица", QString("таблица%1").arg(strNum)).toLower());  // в контексте печати наименования данных хранятся в нижнем регистре
            }
            else
            {
                // ячейка не относится к таблице
                int lpos = cellText.indexOf("]", fpos) + 1; // получим выражение "[<...>]" полностью
                value = cellText.mid(fpos, lpos - fpos);
                value = value.remove("[").remove("]");      // освободим его от квадратных скобок
                var = context->value(value.toLower());      // и получим данные для него из контекста печати
            }
            if (!var.isNull())                                      // если данные имеются
                writeCell(cells.at(i), "[" + value + "]", var);     // то запишем их вместо текста шаблона
            else
            {
                // данных для выражения нет
                if (strNum == 1)                    // выведем сообщение об ошибке (для таблицы это будет только для первой строки)
                    TApplication::exemplar()->showError(QString(QObject::trUtf8("Неизвестное выражение %1")).arg(value));
                result = false;
                break;                      // выйдем из бесконечного цикла
            }
        }
        else
            break;  // элементов "[<...>]" в выражении больше нет, выходим
    }
    return result;
}


QString OOXMLReportEngine::getTableVariable(QDomElement cell)
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
        if (dvar.left(7).toLower() == "таблица")                    // Если выражение начинается со слова "таблица" (т.е. "[таблица<...>]")
        {
            return dvar;   // то значит в этой ячейке начинается табличная часть документа (тело таблицы, не шапка)
        }
    }
    return "";
}


void OOXMLReportEngine::writeCell(QDomNode n, QString svar, QVariant var)
//  Записывает в узел n XML модели документа значение var вместо выражения svar
{
    QString cellText = n.toElement().text().trimmed();
    QString type = "string";        // тип записываемого значения с точки зрения OpenOffice
    QString valueString;

    // Определим тип записываемого значения, преобразуем его в строку
    if ((var.type() == QVariant::Double) ||
        (var.type() == QVariant::Int) ||
        (var.type() == QVariant::UInt))
    {
        valueString = QString("%1").arg(var.toDouble());        // это числовое значение
        type = "float";                                         // в OpenOffice оно имеет тип "float"
    }
    else
    {
        // все остальные значения в OpenOffice будут иметь значение "string"
        if (var.type() == QVariant::DateTime)
            valueString = var.toDateTime().toString("dd.MM.yyyy hh:mm:ss");
        else
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
}


