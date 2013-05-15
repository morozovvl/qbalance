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
    app = TApplication::exemplar();
}


OOXMLReportEngine::~OOXMLReportEngine()
{
}


bool OOXMLReportEngine::open(QString fileName, QMap<QString, QVariant>* cont)
{
    templateFileName = fileName;
    context = cont;
    // Создадим временный каталог
    QString tmpDir = fileName + ".tmp";
    if (QDir().mkdir(tmpDir))
    {
        // Распакуем файл OpenOffice
        QProcess* unzip = new QProcess();
        unzip->setWorkingDirectory(tmpDir);
#ifdef Q_OS_WIN32
        unzip->start(app->applicationDirPath() + "/unzip", QStringList() << fileName);
#else
        unzip->start("unzip", QStringList() << fileName);
#endif
        if (waitProcessEnd(unzip)) {

            // Запишем контент в файл
            QFile file(tmpDir + "/content.xml");
            if (file.open(QIODevice::ReadOnly))
            {
                if (doc.setContent(&file))
                {
                    file.close();

                    writeVariables();

                    if (file.open(QIODevice::WriteOnly))
                    {
                        QTextStream stream(&file);
                        doc.save(stream, 5);
                    }
                }
                file.close();
            }

            // Запакуем файл OpenOffice обратно
            QProcess* zip = new QProcess();
            zip->setWorkingDirectory(tmpDir);
#ifdef Q_OS_WIN32
            zip->start(app->applicationDirPath() + "/zip", QStringList() << "-r" << fileName << ".");
#else
            zip->start("zip", QStringList() << "-r" << fileName << ".");
#endif
            if (waitProcessEnd(zip)) {

                // удалим временный каталог
                removeDir(tmpDir);

                QProcess* ooProcess = new QProcess();
                ooProcess->start("soffice", QStringList() << "--invisible" << "--quickstart" << fileName);
                if ((!ooProcess->waitForStarted(1000)) && (ooProcess->state() == QProcess::NotRunning))    // Подождем 1 секунду и если процесс не запустился
                    app->showError(QObject::tr("Не удалось запустить") + " Open Office");                  // выдадим сообщение об ошибке
                else
                    return true;
            }
            else
                app->showError(QObject::tr("Не удалось запустить программу") + " zip");
        }
        else
            app->showError(QObject::tr("Не удалось запустить программу") + " unzip");
    }
    return false;
}


bool OOXMLReportEngine::waitProcessEnd(QProcess* proc)
{   // Процедура ждет окончания процесса или истечения 30 секунд
    bool result = true;
    QTimer t;
    t.start(30000);
    QEventLoop loop;
    connect(&t, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(proc, SIGNAL(finished(int, QProcess::ExitStatus)), &loop, SLOT(quit()));
    loop.exec();
    if (proc->exitStatus() != QProcess::NormalExit)
        result = false;
    delete proc;
    return result;
}


bool OOXMLReportEngine::removeDir(QString dirName)
{
    bool result = false;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot |
                                                    QDir::System |
                                                    QDir::Hidden  |
                                                    QDir::AllDirs |
                                                    QDir::Files,
                                                    QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
    return result;
}


void OOXMLReportEngine::writeVariables() {
    QDomNodeList cells = doc.elementsByTagName("text:p");
    QRegExp rx("\\[.+\\]");
    QString type;

    // Сначала вставим табличные переменные
    QDomNode firstRowNode;
    for (int i = 0; i < cells.count() && firstRowNode.isNull(); i++)
    {
        QString cellText = cells.at(i).toElement().text().trimmed();
        int fpos = 0;
        int lpos = 0;
        while (true)
        {
            fpos = cellText.indexOf(rx, lpos);
            if (fpos >= 0)
            {
                lpos = cellText.indexOf("]", fpos) + 1;
                QString svar = cellText.mid(fpos, lpos - fpos);
                QString dvar = QString(svar).remove("[").remove("]");
                if (dvar.left(7).toLower() == "таблица")
                {
                    firstRowNode = cells.at(i).parentNode().parentNode();
                    break;
                }
            }
            else
                break;
        }
    }
    if (!firstRowNode.isNull())
    {
        // Найдена табличная часть
        QDomNode lastNode = firstRowNode;
        bool valFound = true;
        for (int strNum = 1; true && valFound; strNum++)
        {
            QDomNode clone = firstRowNode.cloneNode(true);

            cells = clone.toElement().elementsByTagName("text:p");
            for (int i = 0; i < cells.count() && valFound; i++)
            {
                QString cellText = cells.at(i).toElement().text().trimmed();
                bool error = false;
                bool replacement = false;
                int fpos = 0;
                int lpos = 0;
                type = "string";
                while (true)
                {
                    fpos = cellText.indexOf(rx, lpos);
                    if (fpos >= 0)
                    {
                        lpos = cellText.indexOf("]", fpos) + 1;
                        QString svar = cellText.mid(fpos, lpos - fpos);
                        QString dvar = QString(svar).remove("[").remove("]");
                        if (dvar.left(7).toLower() == "таблица")
                        {
                            QVariant var;
                            QString value = QString(dvar.toLower()).replace("таблица", QString("таблица%1").arg(strNum));
                            if (context->contains(value))
                            {
                                var = context->value(value);

                                if (!var.isNull())                          // Если не было ошибок
                                {
                                    QString valueString;
                                    if ((var.type() == QVariant::Double) ||
                                        (var.type() == QVariant::Int) ||
                                        (var.type() == QVariant::UInt))
                                    {
                                        valueString = QString("%1").arg(var.toDouble());
                                        if (svar == cellText)
                                            type = "float";
                                    }
                                    else
                                    {
                                        if (var.type() == QVariant::DateTime)
                                            valueString = var.toDateTime().toString("dd.MM.yyyy hh:mm:ss");
                                        else
                                            valueString = var.toString().trimmed();
                                    }
                                    cellText.replace(svar, valueString);
                                    replacement = true;
                                }
                                else
                                {
                                    if (strNum == 1)
                                        app->showError(QString(QObject::tr("Неизвестное выражение %1")).arg(dvar));
                                    error = true;
                                    break;
                                }
                            }
                        }
                    }
                    else
                        break;
                }
                if (!error && replacement)
                    writeCell(cells.at(i).parentNode().toElement(), cellText, type);
                else
                {
                    valFound = false;           // Очередное значение переменной не найдено, выйдем из заполнения таблицы
                }
            }
            if (valFound)
                lastNode = firstRowNode.parentNode().insertAfter(clone, lastNode);
        }
        firstRowNode.parentNode().removeChild(firstRowNode);
    }

    // Теперь вставим все оставшиеся переменные
    int counter;
    do {
        counter = 0;
        cells =  doc.elementsByTagName("text:p");
        for (int i = 0; i < cells.count(); i++)
        {
            QString cellText = cells.at(i).toElement().text().trimmed();
            bool error = false;
            bool replacement = false;
            int fpos = 0;
            int lpos = 0;
            type = "string";
            while (true)
            {
                fpos = cellText.indexOf(rx, lpos);
                if (fpos >= 0)
                {
                    lpos = cellText.indexOf("]", fpos) + 1;
                    QString svar = cellText.mid(fpos, lpos - fpos);
                    QString dvar = QString(svar).remove("[").remove("]");

                    QVariant var;
                    QString value;
                    if (dvar.left(7).toLower() != "таблица")
                        value = dvar.toLower();
                    else
                        value = QString(dvar.toLower()).replace("таблица", "таблица1");

                    if (context->contains(value))
                    {
                        var = context->value(value);

                        if (!var.isNull())                          // Если не было ошибок
                        {
                            QString valueString;
                            if ((var.type() == QVariant::Double) ||
                                (var.type() == QVariant::Int) ||
                                (var.type() == QVariant::UInt))
                            {
                                valueString = QString("%1").arg(var.toDouble());
                                if (svar == cellText)
                                    type = "float";
                            }
                            else
                            {
                                if (var.type() == QVariant::DateTime)
                                    valueString = var.toDateTime().toString("dd.MM.yyyy hh:mm:ss");
                                else
                                {
                                    if (var.type() == QVariant::Date)
                                        valueString = var.toDate().toString("dd.MM.yyyy");
                                    else
                                        valueString = var.toString().trimmed();
                                }
                            }
                            cellText.replace(svar, valueString);
                            replacement = true;
                            counter++;
                        }
                        else
                        {
                            app->showError(QString(QObject::tr("Неизвестное выражение %1")).arg(dvar));
                            error = true;
                            break;
                        }
                    }
                }
                else
                    break;
            }
            if (!error && replacement)
                writeCell(cells.at(i).parentNode().toElement(), cellText, type);
        }
    } while (counter > 0);


    // Теперь пропустим результат через скрипты
    cells =  doc.elementsByTagName("text:p");
    for (int i = 0; i < cells.count(); i++)
    {
        QString cellText = cells.at(i).toElement().text().trimmed();
        QVariant var = scriptEngine->evaluate(cellText).toVariant();
        type = "string";
        if (!scriptEngine->hasUncaughtException())                          // Если не было ошибок
        {
            QString valueString;
            if ((var.type() == QVariant::Double) ||
                (var.type() == QVariant::Int) ||
                (var.type() == QVariant::UInt))
            {
                valueString = QString("%1").arg(var.toDouble());
                type = "float";
            }
            else
                valueString = var.toString().trimmed();
            writeCell(cells.at(i).parentNode().toElement(), valueString, type);
        }
    }
}


void OOXMLReportEngine::writeCell(QDomElement node, QString value, QString type) {
    // Заполним ячейку
    QDomElement cellNode = node.toElement();
    if (cellNode.tagName() != "table:table-cell")                  // Установим тег ячейки
        cellNode.setTagName("table:table-cell");
    cellNode.setAttribute("office:value-type", type);           // Установим атрибут с типом значения ячейки
    if (type == "float")
        cellNode.setAttribute("office:value", value);
    QDomElement textElement = node.firstChildElement("text:p");
    if (!textElement.isNull())
        node.removeChild(textElement);
    if (value.size() > 0) {
        QDomElement element = doc.createElement("text:p");
        QDomText text = doc.createTextNode(value);
        element.appendChild(text);
        node.appendChild(element);
    }
}


/*
void OOXMLReportEngine::writeTableBody(QDomNode firstRowNode, int pos) {
    QDomNode node;
    int i;
    QDomNode clone = firstRowNode.cloneNode(true);                 // Скопируем строку таблицы
    // Проверим наличие атрибута "number-columns-repeated". Если этот атрибут имеется, значит клетки повторяются
    bool hasRepeated;
    do {
        hasRepeated = false;             // Будем считать, что повторяющиеся элементы не встретятся
        for (QDomNode el = clone.firstChild(); !el.isNull(); el = el.nextSibling()) {
            if (el.toElement().hasAttribute("table:number-columns-repeated")) {
                hasRepeated = true;     // Повтор. элемент все же встретился, обработаем его и повторим просмотр сначала
                int q = el.toElement().attribute("table:number-columns-repeated").toInt() - 1;
                for (int c = 0; c < q; c++) {
                    el.toElement().removeAttribute("table:number-columns-repeated");
                    QDomNode newChild = el.cloneNode(true);
                    clone.insertAfter(newChild, el);
                }
            }
        }
    } while (hasRepeated);
    // Добавим новые строки и заполним их данными из таблицы
    QDomNode tableNode = firstRowNode.parentNode();
    QSqlTableModel* table = parent->getTableModel();
    for (i = 0; i < table->rowCount(); i++) {
        QSqlRecord record = table->record(i);
        node = clone.cloneNode(true);                               // Скопируем строку
        QDomNode cellElement;
        if (node.firstChild().isNull()) {
            for (int j = 0; j < columns.count(); j++) {                 // Для всех полей, которые нам нужно вывести
                cellElement = doc.createElement("table:table-cell");
                writeCell(cellElement.toElement(), record.field(columns.at(j)).value(), record.field(columns.at(j)).type());
                node.appendChild(cellElement);
            }
        }
        else {
            cellElement = node.firstChild();
            for (int p = 0; p < pos; p++)
                cellElement = cellElement.nextSibling();
            for (int j = 0; j < columns.count(); j++) {                 // Для всех полей, которые нам нужно вывести
                writeCell(cellElement.toElement(), record.field(columns.at(j)).value(), record.field(columns.at(j)).type());
                cellElement = cellElement.nextSibling();
            }
        }
        tableNode.appendChild(node);
    }
}
*/



/*
QString OOXMLReportEngine::prepareDefaultDocument(QString fileName) {
    qDebug() << fileName;
    QString contentXMLFile;
    QString result = "";
    QString tmpFile = app->applicationDirPath() + "/tmp/" + fileName;
    QFile dstFile( tmpFile);       // Удалим файл назначения, иначе будет ошибка при копировании
    dstFile.remove();
    dstFile.close();

    QTemporaryFile xmlFile;
    xmlFile.setAutoRemove(true);
    xmlFile.setFileTemplate("tmp_XXXXXX");
    contentXMLFile = xmlFile.fileName();
//    xmlFile.remove();
//    xmlFile.close();
    QFile srcFile(fileName);
    if (!srcFile.exists()) {            // Если файл отчета не существует, то создадим его из пустого шаблона
    }
    qDebug() << srcFile.fileName();
    qDebug() <<  tmpFile + "/" + fileName;
    qDebug() <<  tmpFile + "/" + contentXMLFile;
    if (srcFile.copy( tmpFile + "/" +  fileName)) {
        QProcess* unzip = new QProcess();
        unzip->setWorkingDirectory(QFileInfo(fileName).path());
        unzip->start("unzip", QStringList() <<  fileName << contentXMLFile);
        if (!((!unzip->waitForStarted(1000)) && (unzip->state() == QProcess::NotRunning))) {
            if (writeDefaultDocument( tmpFile + "/" + contentXMLFile)) {
                QProcess* zip = new QProcess();
                zip->setWorkingDirectory( tmpFile);
                zip->start("zip", QStringList() <<  fileName << contentXMLFile);
                if (!((!zip->waitForStarted(1000)) && (zip->state() == QProcess::NotRunning))) {
                    result =  tmpFile + "/" +  fileName;
                }
                else
                    app->showError(QObject::tr("Не удалось запустить программу") + " zip");
            }
            else
                app->showError(QObject::tr("Не удалось изменить содержимое шаблона") + " <" + fileName + ">");
        }
        else
            app->showError(QObject::tr("Не удалось запустить программу") + " unzip");
    }
    else
        app->showError(QString(QObject::tr("Не удалось скопировать шаблон <%1> в каталог %2")).arg(fileName).arg( tmpFile));
    srcFile.close();
    return result;
}

bool OOXMLReportEngine::writeDefaultDocument(QString fileName) {
    bool result = false;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        if (doc.setContent(&file)) {
            file.close();
            // Найдем тег с шапкой таблицы
            rootElement = doc.documentElement();
            tableElement = rootElement.elementsByTagName("table:table").at(0).toElement();     // Будем работать с первой таблицей
            QDomNode headElement = tableElement.firstChildElement("table:table-row");
            QDomNode node = findAnnotation(HEAD_ANNOTATION);             // Поищем аннотации для шапки
            if (node.isNull()) {                                         // Если не найдены аннотации для шапки
                headElement.removeChild(headElement.firstChild());       // В новой пустой строке есть элемент <table:table-cell/>, уберем его
                writeTableHeader(headElement);                           // то создадим шапку заново
            }
            readAvailableColumns();                                      // Прочитаем из отчета, какие нужно вывести колонки
            node = findAnnotation(BODY_ANNOTATION);
            QDomNode firstRow;
            if (!node.isNull()) {                                   // Если найдена аннотация для тела таблицы
                firstRow = node.parentNode();                       // firstRow - узел первой строки тела таблицы
                while (tableElement.lastChild() != firstRow)             // Удалим последующие непустые строки
                    tableElement.removeChild(tableElement.lastChild());
                int i;
                QDomNode firstCell = firstRow.firstChild();
                for (i = 0; firstCell != node; i++)                      // Посчитаем, с какой ячейки слева начинается содержимое таблицы (чтобы можно было вставить пустой столбец)
                    firstCell = firstCell.nextSibling();
                writeTableBody(firstRow, i);
                tableElement.removeChild(firstRow);
            }
            else {
                firstRow = doc.createElement("table:table-row");
                QDomNode cellElement = doc.createElement("table:table-cell");
                writeCellAnnotation(cellElement.toElement(), BODY_ANNOTATION);      // Запишем аннотацию
                firstRow.appendChild(cellElement);
                tableElement.appendChild(firstRow);   // иначе добавим новую пустую строку
                writeTableBody(firstRow, 0);
            }
            writeVariables();
            if (file.open(QIODevice::WriteOnly)) {
                QTextStream stream(&file);
                doc.save(stream, 5);
                result = true;
            }
            else
                app->showError(QObject::tr("Не удалось открыть для записи шаблон") + " <" + fileName + ">");
        }
        else {
            app->showError(QObject::tr("Не удалось загрузить содержимое шаблона") + " <" + fileName + ">");
            file.close();
        }
    }
    else
        app->showError(QObject::tr("Не удалось открыть шаблон") + " <" + fileName + ">");
    return result;
}


void OOXMLReportEngine::writeTableHeader(QDomNode node) {
    QSqlQuery query = parent->getColumnsHeaders();
    while (query.next()) {
        QDomElement cellElement = doc.createElement("table:table-cell");
        writeCell(cellElement, query.record().value("заголовок"));
        writeCellAnnotation(cellElement, QString("%1:%2").arg(HEAD_ANNOTATION).arg(query.record().value("столбец").toString().trimmed()));
        node.appendChild(cellElement);
        }
}


void OOXMLReportEngine::writeTableBody(QDomNode firstRowNode, int pos) {
    QDomNode node;
    int i;
    QDomNode clone = firstRowNode.cloneNode(true);                 // Скопируем строку таблицы
    // Проверим наличие атрибута "number-columns-repeated". Если этот атрибут имеется, значит клетки повторяются
    bool hasRepeated;
    do {
        hasRepeated = false;             // Будем считать, что повторяющиеся элементы не встретятся
        for (QDomNode el = clone.firstChild(); !el.isNull(); el = el.nextSibling()) {
            if (el.toElement().hasAttribute("table:number-columns-repeated")) {
                hasRepeated = true;     // Повтор. элемент все же встретился, обработаем его и повторим просмотр сначала
                int q = el.toElement().attribute("table:number-columns-repeated").toInt() - 1;
                for (int c = 0; c < q; c++) {
                    el.toElement().removeAttribute("table:number-columns-repeated");
                    QDomNode newChild = el.cloneNode(true);
                    clone.insertAfter(newChild, el);
                }
            }
        }
    } while (hasRepeated);
    // Добавим новые строки и заполним их данными из таблицы
    QDomNode tableNode = firstRowNode.parentNode();
    QSqlTableModel* table = parent->getTableModel();
    for (i = 0; i < table->rowCount(); i++) {
        QSqlRecord record = table->record(i);
        node = clone.cloneNode(true);                               // Скопируем строку
        QDomNode cellElement;
        if (node.firstChild().isNull()) {
            for (int j = 0; j < columns.count(); j++) {                 // Для всех полей, которые нам нужно вывести
                cellElement = doc.createElement("table:table-cell");
                writeCell(cellElement.toElement(), record.field(columns.at(j)).value(), record.field(columns.at(j)).type());
//                if (i == 0 && j == 0)                                        // Для первого элемента в первой строчке
//                    writeCellAnnotation(cellElement.toElement(), BODY_ANNOTATION);      // Запишем аннотацию
                node.appendChild(cellElement);
            }
        }
        else {
            cellElement = node.firstChild();
            for (int p = 0; p < pos; p++)
                cellElement = cellElement.nextSibling();
            for (int j = 0; j < columns.count(); j++) {                 // Для всех полей, которые нам нужно вывести
                writeCell(cellElement.toElement(), record.field(columns.at(j)).value(), record.field(columns.at(j)).type());
//                if (i == 0 && j == 0)                                        // Для первого элемента в первой строчке
//                    writeCellAnnotation(cellElement.toElement(), BODY_ANNOTATION);      // Запишем аннотацию
                cellElement = cellElement.nextSibling();
            }
        }
        tableNode.appendChild(node);
    }
//    else {
//        QDomNode cellElement;
//        cellElement = doc.createElement("table:table-cell");
//        writeCellAnnotation(cellElement.toElement(), BODY_ANNOTATION);      // Запишем аннотацию
//        tableNode.appendChild(cellElement);
//    }
}


void OOXMLReportEngine::writeTableEnd(QDomNode node) {
    node = node;
}


void OOXMLReportEngine::writeCellAnnotation(QDomElement node, QString annotation) {
    if (annotation.size() > 0) {
       QDomElement annotationElement = doc.createElement("office:annotation");
       QDomElement annotationText = doc.createElement("text:p");
       QDomText text = doc.createTextNode(annotation);
       annotationText.appendChild(text);
       annotationElement.appendChild(annotationText);
       node.appendChild(annotationElement);
    }
}


QDomNode OOXMLReportEngine::findAnnotation(QString nodeAnnotation) {
    QDomNodeList annotations = rootElement.elementsByTagName("office:annotation");
    for (int i = 0; i < annotations.count(); i++) {
        if (annotations.at(i).firstChildElement("text:p").toElement().text().toLower().left(nodeAnnotation.size()) == nodeAnnotation) {
            return annotations.at(i).parentNode();  // Нашли аннотацию, вернем ячейку, в которой встретилась аннотация
        }
    }
    return (QDomNode());        // Не нашли нужной аннотации, вернем пустое значение
}


void OOXMLReportEngine::readAvailableColumns() {
    QDomNode headNode = findAnnotation(HEAD_ANNOTATION);
    if (!headNode.isNull()) {
        do {
            QString column = headNode.firstChildElement("office:annotation").firstChildElement("text:p").text();
            column = column.remove(QString(HEAD_ANNOTATION) + ":");
            if (column.size() > 0)
                columns.append(column);
            headNode = headNode.nextSibling();
        } while (!headNode.isNull());     // Пока есть еще элемент в этой строчке
    }
}


*/
