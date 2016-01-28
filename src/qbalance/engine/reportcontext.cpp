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

#include <QRegExp>
#include <QDebug>
#include "reportcontext.h"


ReportContext::ReportContext(QHash<QString, QVariant>* d, QObject *parent/* = 0*/) :
    QObject(parent)
{
    data = d;
    rowCount = 0;
    showRepeat = true;
    lastStrNum = 0;
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
//    QRegExp rm("^\\D+\\.");
    QVariant result, lastResult;
    QString lastTag;
    QString pref = tag.left(tag.indexOf("."));
    tag = tag.toLower();
    tag.remove(pref);
    tag = QString("%1%2%3").arg(pref).arg(sortRef.empty() ? strNum : sortRef.value(strNum)).arg(tag);
    lastTag = QString("%1%2%3").arg(pref).arg(sortRef.empty() ? strNum - 1 : sortRef.value(strNum - 1)).arg(tag);
    result = data->value(tag);
/*
    lastResult = lastData->value(lastTag);
    if (!showRepeat && result == lastResult)
    {

    }
*/
    qDebug() << tag << strNum << result;
    return result;
}


void ReportContext::setValue(QString tag, QVariant val)
{
    tag = tag.toLower();
    if (data->contains(tag))
    {
        data->remove(tag);
    }
    data->insert(tag, val);
}


void ReportContext::setValue(QString tag, QVariant val, int strNum)
{
    QString pref = tag.left(tag.indexOf("."));
    tag = tag.toLower();
    tag.remove(pref);
    if (pref == "таблица" && !fieldsInTable.contains(tag))
        fieldsInTable.append(pref + tag);
    tag = QString("%1%2%3").arg(pref).arg(sortRef.empty() ? strNum : sortRef.value(strNum)).arg(tag);
    setValue(tag, val);
    if (strNum > rowCount)
        rowCount = strNum;
}


void ReportContext::removeValue(QString tag)
{
    tag = tag.toLower();
    foreach (QString key, data->keys())
    {
        QRegExp rx("^" + tag + ".*$");
        if (rx.exactMatch(key))
        {
            data->remove(key);
        }
    }
}


void ReportContext::sortTable()        // сортировка контекста печати в разделе таблица по заданному полю
{
    QMultiMap<QString, int>    d;
    QString key;
    for (int i = 1; i <= rowCount; i++)
    {
        key = "";
        for (int j = 0; j < sortOrder.count(); j++)
            key.append(getValue(sortOrder.at(j), i).toString().trimmed() + " ");
        d.insert(key, i);
    }

    int row = 1;
    foreach (QString key, d.keys())
    {
        sortRef.insert(row, d.value(key));
        row++;
    }
}

