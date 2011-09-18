#include <QDir>
#include <QDomElement>
#include <QProcess>
#include <QScriptValue>
#include <QSqlTableModel>
#include "reporttemplate.h"
#include "app.h"
#include "essence.h"
#include "reportengine.h"

ReportTemplate::ReportTemplate(Essence* par, ReportEngine* eng, QString fileName) {
    parent = par;
    engine = eng;
    templateFileName = fileName;
}

bool ReportTemplate::doOpen() {
    bool result = false;
    QString file;
    file = prepareDefaultDocument(templateFileName);
    if (file.size() > 0) {                // Если с файлом отчета все нормально
        result = startOpenOffice(file);          // то запустим Open Office
    }
    return result;
}

bool ReportTemplate::startOpenOffice(QString fileName) {
    bool result = true;
    QProcess* ooProcess = new QProcess();
    ooProcess->setWorkingDirectory(REPORT_DIR);
    ooProcess->start("soffice", QStringList() << fileName);
    if ((!ooProcess->waitForStarted(1000)) && (ooProcess->state() == QProcess::NotRunning)) {   // Подождем 1 секунду и если процесс не запустился
        TApplication::exemplar()->showError(QObject::tr("Не удалось запустить") + " Open Office");                   // выдадим сообщение об ошибке
        result = false;
    }
    return result;
}

QString ReportTemplate::prepareDefaultDocument(QString fileName) {
    qDebug() << fileName;
    QString contentXMLFile;
    QFileInfo file(fileName);
    QString result = "";
    QDir tmpDir(QDir::currentPath() + "/tmp");
    QFile dstFile(tmpDir.path() + "/" + file.fileName());       // Удалим файл назначения, иначе будет ошибка при копировании
    dstFile.remove();
    dstFile.close();
//    QFile xmlFile(tmpDir.path() + "/" + contentXMLFile);
    QTemporaryFile xmlFile;
    xmlFile.setAutoRemove(true);
    xmlFile.setFileTemplate("tmp_XXXXXX");
    contentXMLFile = xmlFile.fileName();
//    xmlFile.remove();
//    xmlFile.close();
    QFile srcFile(fileName);
    if (!srcFile.exists()) {            // Если файл отчета не существует, то создадим его из пустого шаблона
        QString file1Name = REPORT_DIR;
        file1Name += "/";
        file1Name += DEFAULT_REPORT;
        QFile file1(file1Name);
        file1.copy(fileName);
    }
    qDebug() << srcFile.fileName();
    qDebug() << tmpDir.path() + "/" + file.fileName();
    qDebug() << tmpDir.path() + "/" + contentXMLFile;
    if (srcFile.copy(tmpDir.path() + "/" + file.fileName())) {
        QProcess* unzip = new QProcess();
        unzip->setWorkingDirectory(tmpDir.path());
        unzip->start("unzip", QStringList() << file.fileName() << contentXMLFile);
        if (!((!unzip->waitForStarted(1000)) && (unzip->state() == QProcess::NotRunning))) {
            if (writeDefaultDocument(tmpDir.path() + "/" + contentXMLFile)) {
                QProcess* zip = new QProcess();
                zip->setWorkingDirectory(tmpDir.path());
                zip->start("zip", QStringList() << file.fileName() << contentXMLFile);
                if (!((!zip->waitForStarted(1000)) && (zip->state() == QProcess::NotRunning))) {
                    result = tmpDir.path() + "/" + file.fileName();
                }
                else
                    TApplication::exemplar()->showError(QObject::tr("Не удалось запустить программу") + " zip");
            }
            else
                TApplication::exemplar()->showError(QObject::tr("Не удалось изменить содержимое шаблона") + " <" + fileName + ">");
        }
        else
            TApplication::exemplar()->showError(QObject::tr("Не удалось запустить программу") + " unzip");
    }
    else
        TApplication::exemplar()->showError(QString(QObject::tr("Не удалось скопировать шаблон <%1> в каталог %2")).arg(fileName).arg(tmpDir.path()));
    srcFile.close();
    return result;
}

bool ReportTemplate::writeDefaultDocument(QString fileName) {
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
                TApplication::exemplar()->showError(QObject::tr("Не удалось открыть для записи шаблон") + " <" + fileName + ">");
        }
        else {
            TApplication::exemplar()->showError(QObject::tr("Не удалось загрузить содержимое шаблона") + " <" + fileName + ">");
            file.close();
        }
    }
    else
        TApplication::exemplar()->showError(QObject::tr("Не удалось открыть шаблон") + " <" + fileName + ">");
    return result;
}

void ReportTemplate::writeTableHeader(QDomNode node) {
    QSqlQuery query = parent->getColumnsHeaders();
    while (query.next()) {
        QDomElement cellElement = doc.createElement("table:table-cell");
        writeCell(cellElement, query.record().value("заголовок"));
        writeCellAnnotation(cellElement, QString("%1:%2").arg(HEAD_ANNOTATION).arg(query.record().value("столбец").toString().trimmed()));
        node.appendChild(cellElement);
        }
}

void ReportTemplate::writeTableBody(QDomNode firstRowNode, int pos) {
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

void ReportTemplate::writeTableEnd(QDomNode node) {
    node = node;
}

void ReportTemplate::writeCellAnnotation(QDomElement node, QString annotation) {
    if (annotation.size() > 0) {
       QDomElement annotationElement = doc.createElement("office:annotation");
       QDomElement annotationText = doc.createElement("text:p");
       QDomText text = doc.createTextNode(annotation);
       annotationText.appendChild(text);
       annotationElement.appendChild(annotationText);
       node.appendChild(annotationElement);
    }
}

void ReportTemplate::writeCell(QDomElement node, QVariant value, QVariant::Type type) {
    QString valueType;
    QString valueString;
    // Определим тип ячейки
    if (type == QVariant::String) {
        valueType = "string";
        valueString = value.toString().trimmed();
    }
    else if ((type == QVariant::Double) ||
             (type == QVariant::Int) ||
             (type == QVariant::UInt)) {
        valueType = "float";
        valueString = QString("%1").arg(QLocale().toString(value.toDouble()));
    }
    // Заполним ячейку
    QDomElement cellNode = node.toElement();
    if (cellNode.tagName() != "table:table-cell")                  // Установим тег ячейки
        cellNode.setTagName("table:table-cell");
    cellNode.setAttribute("office:value-type", valueType);           // Установим атрибут с типом значения ячейки
    if (valueType == "float")
        cellNode.setAttribute("office:value", value.toDouble());
    QDomElement textElement = node.firstChildElement("text:p");
    if (!textElement.isNull())
        node.removeChild(textElement);
    if (valueString.size() > 0) {
        QDomElement element = doc.createElement("text:p");
        QDomText text = doc.createTextNode(valueString);
        element.appendChild(text);
        node.appendChild(element);
    }
}

QDomNode ReportTemplate::findAnnotation(QString nodeAnnotation) {
    QDomNodeList annotations = rootElement.elementsByTagName("office:annotation");
    for (int i = 0; i < annotations.count(); i++) {
        if (annotations.at(i).firstChildElement("text:p").toElement().text().toLower().left(nodeAnnotation.size()) == nodeAnnotation) {
            return annotations.at(i).parentNode();  // Нашли аннотацию, вернем ячейку, в которой встретилась аннотация
        }
    }
    return (QDomNode());        // Не нашли нужной аннотации, вернем пустое значение
}

void ReportTemplate::readAvailableColumns() {
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

void ReportTemplate::writeVariables() {
    QDomNodeList cells = doc.elementsByTagName("text:p");
    for (int i = 0; i < cells.count(); i++) {
        if (cells.at(i).parentNode().toElement().tagName() == "table:table-cell") {
            QString cellText = cells.at(i).toElement().text().trimmed();
            if (((cellText.left(5) == "&lt;:") || (cellText.left(2) == "<:")) &&
                (cellText.right(2) == ":>")) {
                cellText = cellText.remove("&lt;:");
                cellText = cellText.remove("<:");
                cellText = cellText.remove(":>");
                QVariant var = engine->getEngine()->evaluate(cellText).toVariant();
                if (!engine->getEngine()->hasUncaughtException() && !var.isNull())                          // Если не было ошибок
                    writeCell(cells.at(i).parentNode().toElement(), var);
                else
                    TApplication::exemplar()->showError(QString(QObject::tr("Неизвестное выражение %1 в шаблоне <%2>.")).arg(cellText).arg(templateFileName));
            }
        }
    }
}
