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
#include <QDebug>
#include "ooxmlengine.h"


OOXMLEngine::OOXMLEngine(): QObject()
{
    app = TApplication::exemplar();
}


OOXMLEngine::~OOXMLEngine()
{
}


bool OOXMLEngine::open(QString fName, bool ro)
{
    fileName = fName;
    readOnly = ro;
    templateFileName = fileName;
    // Создадим временный каталог
    QTemporaryFile templateFile;
    templateFile.setFileTemplate(QDir().tempPath() + "/tmp_XXXXXX");
    templateFile.open();
    tmpDir = templateFile.fileName() + ".tmp";
    templateFile.close();
    if (QDir().mkdir(tmpDir))
    {
        // Распакуем файл шаблона документа OpenOffice
        QProcess* unzip = new QProcess();
        unzip->setWorkingDirectory(tmpDir);
#ifdef Q_OS_WIN32
        unzip->start(app->applicationDirPath() + "/unzip", QStringList() << fileName);
#else
        unzip->start("unzip", QStringList() << fileName);
#endif

        // Если удалось распаковать, то продолжим
        if (app->waitProcessEnd(unzip))
        {
            QFile file(tmpDir + "/content.xml");
            if (file.open(QIODevice::ReadOnly))
            {
                if (doc.setContent(&file))
                {
                    file.close();
                    return true;
                }
            }
        }
        else
            app->showError(QObject::trUtf8("Не удалось запустить программу") + " unzip");
    }
    return false;
}


void OOXMLEngine::close()
{
    if (!readOnly)
    {
        QFile file(tmpDir + "/content.xml");
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            doc.save(stream, 5);
            file.close();

            // Запакуем файл OpenOffice обратно
            QProcess* zip = new QProcess();
            zip->setWorkingDirectory(tmpDir);
#ifdef Q_OS_WIN32
            zip->start(app->applicationDirPath() + "/zip", QStringList() << "-r" << fileName << ".");
#else
            zip->start("zip", QStringList() << "-r" << fileName << ".");
#endif

            // Если удалось запаковать, то продолжим
            if (app->waitProcessEnd(zip))
            {
                // удалим временный каталог
                removeDir(tmpDir);
            }
            else
                app->showError(QObject::trUtf8("Не удалось запустить программу") + " zip");
        }
    }
    else
        removeDir(tmpDir);
}


bool OOXMLEngine::removeDir(QString dirName)
// удаляет времменный каталог, в котором разворачивался архив файла OpenOffice
{
    bool result = false;
    QDir dir(dirName);

    if (dir.exists(dirName))
    {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot |
                                                    QDir::System |
                                                    QDir::Hidden  |
                                                    QDir::AllDirs |
                                                    QDir::Files,
                                                    QDir::DirsFirst))
        {
            if (info.isDir())
                result = removeDir(info.absoluteFilePath());
            else
                result = QFile::remove(info.absoluteFilePath());

            if (!result)
                return result;
        }
        result = dir.rmdir(dirName);
    }
    return result;
}


QDomElement OOXMLEngine::getCell(int row, int column, QDomDocument* document)
{
    QDomNode rowNode;
    if (row >= 0 && column >= 0)
    {
        QDomNodeList cells;
        QDomDocument* docum = (document == 0) ? &doc : document;   // Если задан документ, в котором искать
        cells = docum->elementsByTagName("table:table-row");   // будем просматривать все строки
        if (row <= cells.count())
        {
            rowNode = cells.at(row);

            // Теперь будем просматривать ячейки в строке
            QDomNodeList nodeList = rowNode.childNodes();

            int counter = 0;
            int nodeListQuan = nodeList.count();
            for (int i = 0; i < nodeListQuan; i++)
            {
                QDomElement element = nodeList.at(i).toElement();
                if (element.hasAttribute("table:number-columns-repeated"))
                {
                    int repeated = QString(element.attribute("table:number-columns-repeated")).toInt();
                    if (column >= counter && column < counter + repeated)
                        return element;
                    counter = counter + repeated;
                }
                else
                {
                    if (counter == column)
                        return element;
                    counter++;
                }
            }
        }
    }
    return rowNode.toElement();     // Ячейка не найдена, вернем пустую
}


QString OOXMLEngine::getCellText(QDomElement element)
{
    return getCell(row(element), column(element)).firstChildElement("text:p").text().trimmed();
}


QString OOXMLEngine::getCellText(int row, int column)
{
    return getCell(row, column).firstChildElement("text:p").text().trimmed();
}


QDomElement OOXMLEngine::getCellWithAnnotation(QString annotation)
{
    QDomNode rowNode;
    QDomNodeList cells;
    cells = doc.elementsByTagName("office:annotation");   // будем просматривать аннотации
    int cellsQuan = cells.count();
    for (int i = 0; i < cellsQuan; i++)
    {
        if (cells.at(i).toElement().elementsByTagName("text:p").at(0).toElement().text() == annotation)
        {
            return cells.at(i).parentNode().toElement();
        }
    }
    return rowNode.toElement();     // Ячейка не найдена, вернем пустую
}


int OOXMLEngine::row(QDomElement cell)
{
    QDomNodeList cells;
    cells = cell.ownerDocument().elementsByTagName("table:table-row");   // будем просматривать все строки
    int cellsQuan = cells.count();
    for (int i = 0; i < cellsQuan; i++)
    {
        if (cells.at(i) == cell.parentNode())
            return i;
    }
    return -1;
}


int OOXMLEngine::column(QDomElement cell)
{
    int counter = 0;
    QDomNodeList nodeList = cell.parentNode().childNodes();
    for (int i = 0; i < nodeList.count(); i++)
    {
        QDomElement element = nodeList.at(i).toElement();
        if (element.hasAttribute("table:number-columns-repeated"))
            counter = counter + QString(element.attribute("table:number-columns-repeated")).toInt();
        else
        {
            if (element == cell)
                return counter;
            counter++;
        }
    }
    return -1;
}


void OOXMLEngine::writeCell(QDomNode n, QString cellText, QString type)
//  Записывает в узел n XML модели документа значение cellText типа type
{
    QDomElement node = n.parentNode().toElement();
    if (node.tagName() != "table:table-cell")                  // Установим тег ячейки
        node.setTagName("table:table-cell");
    node.setAttribute("office:value-type", type);               // Установим атрибут с типом значения ячейки
    node.setAttribute("calcext:value-type", type);              // Установим атрибут с типом значения ячейки
    node.setAttribute("office:value", cellText);
    QDomElement textElement = node.firstChildElement("text:p");
    if (!textElement.isNull())
        node.removeChild(textElement);
    QDomElement element = doc.createElement("text:p");
    QDomText text = doc.createTextNode(cellText);
    element.appendChild(text);
    node.appendChild(element);
}




