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

#include "saldo.h"
#include "../kernel/app.h"
#include "../kernel/dictionaries.h"
#include "../gui/tableview.h"
#include "../storage/mysqlrelationaltablemodel.h"
#include "../storage/dbfactory.h"


Saldo::Saldo(QString, QString dictName, QObject *parent): Dictionary(dictName, parent) {
}


Saldo::~Saldo()
{
}


void Saldo::postInitialize(QString cAcc, QString dictName, QObject *parent)
{
    Dictionary::postInitialize(dictName, parent);

    account = cAcc;
    formTitle = QString(QObject::trUtf8("Остатки на %1 счете").arg(account));
    dictionaryName = dictName.trimmed().toLower();
    tagName = "saldo" + cAcc;
    scriptFileName =  tagName + ".qs";
    quan = false;
    lIsSaldo = true;
    getIdRefresh = false;
    quan = db->getAccountsValue(cAcc, "КОЛИЧЕСТВО").toBool();
    lInsertable = false;
    lDeleteable = false;
    lUpdateable = false;
    lPrintable = false;
}


QString Saldo::objectName()
{
    return "Saldo";
}


void Saldo::setQuan(bool q)
{
    quan = q;
    tableModel->selectStatement();
}


bool Saldo::setTableModel(int)
{
    if (Dictionary::setTableModel(0))
    {
        QString selectStatement = tableModel->getSelectStatement();

        QString tName = db->getObjectName("сальдо");
        QList<FieldType> fields;
        db->getColumnsProperties(&fields, tName);

        QString selectList;
        FieldType fld;
        for (int i = 0; i < fields.count(); i++)
        {
            fld = fields.at(i);
            if ((QString(fields.at(i).name).compare("конкол",    Qt::CaseInsensitive) == 0) ||
                (QString(fields.at(i).name).compare("концена",   Qt::CaseInsensitive) == 0) ||
                (QString(fields.at(i).name).compare("консальдо", Qt::CaseInsensitive) == 0))
            {
                QString column = QString("%1__%2").arg(fld.table).arg(fld.column).toUpper();
                selectList.append(QString(", \"%1\".\"%2\" AS \"%3\"").arg(fld.table)
                                                                      .arg(fld.name)
                                                                      .arg(column));
                fld.column = column;
                fld.header = column;
                columnsProperties.append(fld);
            }
        }
        selectStatement.replace(" FROM", selectList + " FROM");
        selectStatement.append(QString(" INNER JOIN \"%1\" ON \"%1\".\"%2\"='%3' AND \"%1\".\"%4\"=\"%5\".\"%6\"").arg(tName)
                                                                                                                .arg(db->getObjectName(dictionaryName + ".счет"))
                                                                                                                .arg(account)
                                                                                                                .arg(db->getObjectName(tName + ".код"))
                                                                                                                .arg(dictionaryName)
                                                                                                                .arg(db->getObjectName(dictionaryName + ".код")));
        tableModel->setSelectStatement(selectStatement);
        db->getColumnsRestrictions(tName, &columnsProperties);
        return true;
    }
    return false;
}


void Saldo::lock(bool toLock)
// Заблокировать все связанные справочники
{
    if (toLock)
    {
        Dictionary* dict = dictionaries->getDictionary(dictionaryName);
        int id = getValue(idFieldName).toInt();
        if (id > 0)
            dict->setId(id);
        dict->lock();
        locked = true;
    }
    else
        locked = false;
}


void Saldo::setOrderClause(QString sOrder)
{
    QString sortOrder = sOrder;
    if (isSet())
    {
        QStringList tablesList;
        QString tName = db->getObjectName("сальдо");
        for (int i = 0; i < columnsProperties.count(); i++)
        {
            FieldType fld = columnsProperties.at(i);
            if (fld.table != tName && fld.table != tableName && !tablesList.contains(fld.table) && fld.table.left(9) != "документы" && fld.table.left(11) != "докатрибуты")
            {
                tablesList.append(fld.table);
                if (sortOrder.size() > 0)
                    sortOrder.append(",");
                sortOrder.append(QString("\"%1\".%2").arg(fld.table)
                                                     .arg(db->getObjectNameCom(fld.table + ".имя")));
            }
        }
    }
    else
    {
        if (sortOrder.size() > 0)
            sortOrder.append(",");
        sortOrder.append(QString("\"%1\".%2").arg(tableName)
                                             .arg(db->getObjectNameCom(tableName + ".имя")));
    }
    Table::setOrderClause(sortOrder);
}


QString Saldo::transformSelectStatement(QString statement) {
    QString tName = db->getObjectName("сальдо");
    QString command = statement;
    QString appendString;
    if (quan)
        appendString.append(QString(" AND (\"%1\".\"%2\"<>0 OR \"%1\".\"%3\"<>0)").arg(tName)
                                                                                  .arg(db->getObjectName(tName + ".конкол"))
                                                                                  .arg(db->getObjectName(tName + ".консальдо")));
    if (command.contains(" ORDER BY", Qt::CaseInsensitive))
        command.replace(QString(" ORDER BY"), appendString + " ORDER BY", Qt::CaseInsensitive);
    else
        command.append(appendString);
    return command;
}


void Saldo::setPhotoPath(QString path)
{
    Essence::setPhotoPath(path);
//    dictionaries->getDictionary(dictionaryName)->setPhotoPath(path);
}


bool Saldo::setId(int id)
{
    if (id > 0)
    {
        bool enabled = photoEnabled;
        photoEnabled = false;
        bool q = quan;                          // Отменим временно ограничение на нулевые остатки сальдо
        quan = false;                           // иначе не все сальдо будут видны
        tableModel->selectStatement();
        db->insertSaldo(account, id);
        query(QString("%1.%2='%3' AND %1.%4=%5").arg(db->getObjectNameCom("сальдо"))
                                        .arg(db->getObjectNameCom("сальдо.СЧЕТ"))
                                        .arg(account)
                                        .arg(db->getObjectNameCom("сальдо.КОД"))
                                        .arg(id));
        grdTable->selectRow(0);
        photoEnabled = enabled;
        quan = q;
        tableModel->selectStatement();
        lock(true);
    }
    return (rowCount() > 0);
}
