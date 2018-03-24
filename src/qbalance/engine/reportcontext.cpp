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

#include <QtCore/QRegExp>
#include <QtSql/QSqlRecord>
#include <QtCore/QDebug>
#include <QtCore/qmath.h>
#include "reportcontext.h"
#include "documentscriptengine.h"


ReportContext::ReportContext(QHash<QString, QVariant>* d, QObject *parent/* = 0*/) :
    QObject(parent)
{
    data = d;
    showRepeat = true;
    lastStrNum = 0;
    tableName = "таблица";
    currentRow = 0;
    scriptEngine = 0;
}


int ReportContext::count()
{
    return data->count();
}


QHash<QString, QVariant>* ReportContext::getData()
{
    return data;
}


QList<QString> ReportContext::getKeysList()
{
    return data->keys();
}


int ReportContext::getRowCount(QString name)
{
    return rowCounts.value(name.size() > 0 ? name : tableName);
}


void ReportContext::clearSortOrder()
{
    sortOrder.clear();
    sortRef.clear();
}


void ReportContext::appendSortOrder(QString order)
{
    sortOrder.append(order);
}


void ReportContext::setShowRepeatValue(bool rep)
{
    showRepeat = rep;
}


void ReportContext::setTableName(QString name)
{
    tableName = name;
}


QString ReportContext::getTableName()
{
    return tableName;
}


QVariant ReportContext::getValue(QString tag)
{
    QVariant result;
    tag = tag.toLower();
    result = data->value(tag);
    return result;
}


QVariant ReportContext::getValue(QString tag, int strNum)
{
    QVariant result;
    if (strNum > 0)
    {
        QString pref = tag.left(tag.indexOf("."));
        if (currentRow > 0)
            strNum = currentRow;
        tag = tag.toLower();
        tag.remove(pref.toLower());
        tag = QString("%1%2%3").arg(pref).arg(sortRef.empty() ? strNum : sortRef.value(strNum)).arg(tag);
    }
    result = data->value(tag.toLower());
    return result;
}


void ReportContext::setValue(QString tag, QVariant val)
{
    if (val.isValid())
    {
        tag = tag.toLower();
        if (data->contains(tag))
        {
            data->remove(tag);
        }
        data->insert(tag, val);
    }
}


void ReportContext::setValue(QString tag, QVariant val, int strNum)
{
    QString pref = tag.left(tag.indexOf("."));
    tag = tag.toLower();
    tag.remove(pref);
    tag = QString("%1%2%3").arg(pref).arg(sortRef.empty() ? strNum : sortRef.value(strNum)).arg(tag);
    setValue(tag, val);
    if (strNum > rowCounts.value(pref))
    {
        rowCounts.remove(pref);
        rowCounts.insert(pref, strNum);
    }
}


void ReportContext::removeValue(QString tag)
{
    tag = tag.toLower() + ".";
    foreach (QString key, data->keys())
    {
        if (key.indexOf(tag) != -1)
        {
            data->remove(key);
        }
    }
}


void ReportContext::sortTable(QString table)        // сортировка контекста печати в разделе таблица по заданному полю
{
    if (table.size() == 0)
        table = tableName;
    QMultiMap<QString, int>    d;
    QString key;
    for (int i = 1; i <= rowCounts.value(table); i++)
    {
        key = "";
        for (int j = 0; j < sortOrder.count(); j++)
            key.append(getValue(sortOrder.at(j), i).toString().trimmed() + " ");
        key = QString("%1_%2").arg(key.trimmed()).arg(i);
        if (key.size() > 0)
            d.insert(key, i);
    }

    int row = 1;
    foreach (QString key, d.keys())
    {
        sortRef.insert(row, d.value(key));
        setValue("таблица.НОМЕРСТРОКИ", row, row);
        row++;
    }
}


void ReportContext::appendPrintValues(QString prefix, QSqlQuery* query)
{
    int i = 1;
    query->first();
    while (query->isValid())
    {
        QSqlRecord rec = query->record();
        for (int j = 0; j < query->record().count(); j++)
        {
            setValue(QString("%1.%2").arg(prefix).arg(query->record().fieldName(j)).toLower(), rec.value(j), i);
        }
        setValue(QString("%1.%2").arg(prefix).arg("номерстроки"), QVariant(i), i);
        query->next();
        i++;
    }
}


void ReportContext::setCurrentRow(int row)
{
    currentRow = row;
}


int ReportContext::getCurrentRow()
{
    return currentRow;
}


void ReportContext::clear()
{
    data->clear();
    lastStrNum = 0;
    currentRow = 0;
    rowCounts.clear();
    clearSortOrder();
}


void ReportContext::setScriptEngine(DocumentScriptEngine* se)
{
    scriptEngine = se;
}
