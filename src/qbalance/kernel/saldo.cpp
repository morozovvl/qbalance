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
#include "../storage/mysqlrelationaltablemodel.h"


Saldo::Saldo(QString cAcc, QString dictName, QObject *parent): Dictionary(dictName, parent) {
    account = cAcc;
    formTitle = QString(QObject::trUtf8("Остатки на %1 счете").arg(account));
    dictionaryName = dictName.trimmed().toLower();
    tagName = "saldo" + cAcc;
    quan = false;
    lIsSaldo = true;
    QSqlQuery accounts = db->getAccounts();
    accounts.first();
    while (accounts.isValid())
    {
        if (accounts.record().value(db->getObjectName("vw_счета.счет")).toString().trimmed().toLower() == cAcc)
        {
            quan = accounts.record().value(db->getObjectName("vw_счета.количество")).toBool();
            break;
        }
        accounts.next();
    }
    lInsertable = false;
    lDeleteable = false;
    lUpdateable = false;
    lPrintable = false;
}


bool Saldo::open()
{
    lIsSet = false;                              // Сальдо не может быть набором
    return Dictionary::open();
}


bool Saldo::setTableModel(int)
{
    if (Dictionary::setTableModel(0))
    {
        QString selectCommand = tableModel->getSelectStatement();

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
        selectCommand.replace(" FROM", selectList + " FROM");
        selectCommand.append(QString(" INNER JOIN \"%1\" ON \"%1\".\"%2\"='%3' AND \"%1\".\"%4\"=\"%5\".\"%6\"").arg(tName)
                                                                                                                .arg(db->getObjectName(dictionaryName + ".счет"))
                                                                                                                .arg(account)
                                                                                                                .arg(db->getObjectName(tName + ".код"))
                                                                                                                .arg(dictionaryName)
                                                                                                                .arg(db->getObjectName(dictionaryName + ".код")));
        tableModel->setSelectStatement(selectCommand);
        db->getColumnsRestrictions(tName, &columnsProperties);
        return true;
    }
    return false;
}


void Saldo::setOrderClause()
{
    Table::setOrderClause("");
}


QString Saldo::transformSelectStatement(QString statement) {
    QString tName = db->getObjectName("сальдо");
    QString command = statement;
    QString appendString = QString(" %1 \"%2\".\"%3\"='%4'").arg(command.contains(" WHERE", Qt::CaseInsensitive) ? " AND":" WHERE")
                                                            .arg(tName)
                                                            .arg(db->getObjectName("счет.счет"))
                                                            .arg(account);
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

