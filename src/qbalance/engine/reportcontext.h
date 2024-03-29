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

#ifndef REPORTCONTEXT_H
#define REPORTCONTEXT_H

#include <QtCore/QObject>
#include <QtCore/QHash>
#include <QtCore/QVariant>
#include <QtCore/QStringList>
#include <QtSql/QSqlQuery>
#include <QtCore/QDebug>

class DocumentScriptEngine;

class ReportContext : public QObject
{
    Q_OBJECT
public:
    ReportContext(QHash<QString, QVariant>*, QObject *parent = 0 /*nullptr*/);
    ~ReportContext();
    Q_INVOKABLE int count();
    Q_INVOKABLE virtual QVariant getValue(QString);
    Q_INVOKABLE virtual QVariant getValue(QString, int);
    Q_INVOKABLE virtual void setValue(QString, QVariant);
    Q_INVOKABLE virtual void setValue(QString, QVariant, int);
    Q_INVOKABLE QHash<QString, QVariant>* getData();
    Q_INVOKABLE QList<QString> getKeysList();
    Q_INVOKABLE void removeValue(QString key);    // Удалить значение, ключ которого начинается с key
    Q_INVOKABLE int getRowCount(QString name = "");
    Q_INVOKABLE void sortTable(QString = "");        // сортировка контекста печати в разделе таблица по заданному полю
    Q_INVOKABLE void clearSortOrder();
    Q_INVOKABLE void appendSortOrder(QString order);
    Q_INVOKABLE void setShowRepeatValue(bool rep);
    Q_INVOKABLE void setTableName(QString name);
    QString getTableName();
    Q_INVOKABLE virtual void appendPrintValues(QString, QSqlQuery*);
    void        setCurrentRow(int);
    int         getCurrentRow();
    void        clear();
    void        setScriptEngine(DocumentScriptEngine* = 0 /*nullptr*/);

private:
    QHash<QString, QVariant>*    data;
    QHash<QString, int>          rowCounts;
    int             lastStrNum;
    QStringList     sortOrder;
    QHash<int, int> sortRef;
    bool            showRepeat;
    QString         tableName;
    int             currentRow;
    DocumentScriptEngine*   scriptEngine;
};

#endif // REPORTCONTEXT_H
