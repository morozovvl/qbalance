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
#include <QtCore/QProcess>
#include <QtCore/QDebug>
#include <QTemporaryFile>
#include "ooxmlengine.h"
#include "../kernel/app.h"


OOXMLEngine::OOXMLEngine(): QObject()
{
    app = TApplication::exemplar();
    showError = true;
}


OOXMLEngine::~OOXMLEngine()
{
}


void OOXMLEngine::setApp(TApplication* a)
{
    app = a;
}


QDomDocument* OOXMLEngine::getDomDocument()
{
    return & doc;
}


int OOXMLEngine::rowCount()
{
    return rowQuan;
}


void OOXMLEngine::setShowError(bool show)
{
    showError = show;
}


bool OOXMLEngine::open(QString fName, bool ro)
{
    return open(fName, "", ro);
}


bool OOXMLEngine::open(QString fName, QString sheet, bool ro)
{
    bool result = false;
    if (QDir().exists(fName))
    {
        fileName = QFileInfo(fName).absoluteFilePath();
        sheetName = sheet;
        readOnly = ro;
        templateFileName = fileName;
        // Создадим временный каталог
        QTemporaryFile templateFile;
        templateFile.setFileTemplate(QDir().tempPath() + "/tmp_" + QFileInfo(fileName).fileName() + "_XXXXXX");
        templateFile.open();
        tmpDir = templateFile.fileName() + ".tmp";
        templateFile.close();
        if (QDir().mkdir(tmpDir))
        {
            // Распакуем файл шаблона документа OpenOffice
            QProcess* unzip = new QProcess();
            unzip->setWorkingDirectory(tmpDir);
#if defined(Q_OS_LINUX)
            unzip->start("unzip", QStringList() << fileName);
#elif defined(Q_OS_WIN)
            unzip->start(app->applicationDirPath() + "/unzip", QStringList() << fileName);
#endif
            app->print(QString(unzip->readAllStandardOutput()));
            // Если удалось распаковать, то продолжим
            if (app->waitProcessEnd(unzip))
            {
                QFile file(tmpDir + "/content.xml");
                if (file.open(QIODevice::ReadOnly))
                {
                    if (doc.setContent(&file))
                    {
                        if (sheetName.size() == 0)
                        {
                            sheetNode = doc;
                            rowCells = doc.elementsByTagName("table:table-row");
                        }
                        else
                        {
                            QDomNodeList cells;
                            cells = doc.elementsByTagName("table:table");
                            int cellsQuan = cells.count();
                            for (int i = 0; i < cellsQuan; i++)
                            {
                                if (cells.at(i).toElement().attribute("table:name") == sheetName)
                                {
                                    sheetNode = cells.at(i).toDocument();
                                    rowCells = cells.at(i).toElement().elementsByTagName("table:table-row");
                                    break;
                                }
                            }
                        }
                        rowQuan = rowCells.count();
                        file.close();
                        result = true;
                    }
                }
            }
            else if (showError)
                app->showError(QObject::trUtf8("Не удалось запустить программу") + " unzip");
            QDir().rmdir(tmpDir);
        }
    }
    else if (showError)
        app->showError(QObject::trUtf8("Не удалось открыть файл ") + fName);
    return result;
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
#if defined(Q_OS_WIN)
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
            else if (showError)
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


QDomElement OOXMLEngine::getCell(int row, int column)
{
    QDomNode rowNode;
    QDomElement element;
    if (row >= 0 && row < rowQuan && column >= 0)
    {
        rowNode = rowCells.at(row);
        if (!rowNode.isNull())
        {
            // Теперь будем просматривать ячейки в строке
            QDomNodeList nodeList = rowNode.childNodes();

            if (!nodeList.isEmpty())
            {
                int counter = 0;
                int repeated;
                for (int i = 0; i < nodeList.count(); i++)
                {
                    element = nodeList.at(i).toElement();
                    if (!element.isNull())
                    {
                        if (element.hasAttribute("table:number-columns-repeated"))
                        {
                            repeated = QString(element.attribute("table:number-columns-repeated")).toInt();
                            if (column >= counter && column < counter + repeated)
                            {
                                return element;
                            }
                            counter = counter + repeated;
                        }
                        else
                        {
                            if (counter == column)
                            {
                                if (!element.isNull())
                                {
                                    return element;
                                }
                            }
                            counter++;
                        }
                    }
                }
            }
        }
    }
    return element;     // Ячейка не найдена, вернем пустую
}


QString OOXMLEngine::getCellText(QDomElement element)
{
    return getCell(row(element), column(element)).firstChildElement("text:p").text().trimmed();
}


QString OOXMLEngine::getCellText(int row, int column)
{
    QString result;
    QDomElement element = getCell(row, column);
    if (!element.isNull())
    {
        if (element.attribute("office:value-type") == "float")
            result = element.attribute("office:value");
        else
        {
            QDomElement refElement = element;
            refElement = refElement.elementsByTagName("text:a").at(0).toElement();
            if (!refElement.isNull())
            {
                result = refElement.attribute("xlink:href");
            }
            else
            {
                element = element.firstChildElement("text:p");
                if (!element.isNull())
                {
                    result = element.text().trimmed();
                }
            }
        }
    }
    return result;
}


QDomElement OOXMLEngine::getCellWithAnnotation(QString annotation)
{
    QDomNode rowNode;
    QDomNodeList cells;
    annotation = annotation.toUpper();
    cells = sheetNode.elementsByTagName("office:annotation");   // будем просматривать аннотации
    int cellsQuan = cells.count();
    for (int i = 0; i < cellsQuan; i++)
    {
        if (cells.at(i).toElement().elementsByTagName("text:p").at(0).toElement().text().toUpper() == annotation)
        {
            return cells.at(i).parentNode().toElement();
        }
    }
    return rowNode.toElement();     // Ячейка не найдена, вернем пустую
}


int OOXMLEngine::row(QDomElement cell)
{
    for (int i = 0; i < rowQuan; i++)
    {
        if (rowCells.at(i) == cell.parentNode())
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




