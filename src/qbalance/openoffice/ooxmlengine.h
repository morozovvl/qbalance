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

#ifndef OOXMLENGINE_H
#define OOXMLENGINE_H
#include <QtCore/QObject>
#include <QtXml/QDomNode>

class TApplication;


class OOXMLEngine: public QObject
{
    Q_OBJECT
public:
    OOXMLEngine();
    ~OOXMLEngine();
    Q_INVOKABLE bool open(QString, bool = false);
    Q_INVOKABLE bool open(QString, QString, bool = false);
    Q_INVOKABLE void close();
    Q_INVOKABLE void setApp(TApplication* a);
    Q_INVOKABLE QDomDocument* getDomDocument();
    Q_INVOKABLE QDomElement getCell(int, int);
    Q_INVOKABLE QString getCellText(QDomElement);
    Q_INVOKABLE QString getCellText(int, int);
    Q_INVOKABLE QDomElement getCellWithAnnotation(QString);
    Q_INVOKABLE int row(QDomElement);
    Q_INVOKABLE int column(QDomElement);
    Q_INVOKABLE void writeCell(QDomNode, QString, QString);
    Q_INVOKABLE int rowCount();
    Q_INVOKABLE void setShowError(bool show);
    QString getTmpDir() { return tmpDir; }


private:
    TApplication*               app;
    QString                     fileName;
    QString                     sheetName;
    QDomDocument                sheetNode;
    QString                     templateFileName;
    QString                     tmpDir;
    QDomDocument                doc;
    QDomNodeList                cells;
    QDomNodeList                rowCells;
    int                         rowQuan;
    bool                        readOnly;
    bool                        showError;

    bool removeDir(QString);
};

#endif // OOXMLENGINE_H
