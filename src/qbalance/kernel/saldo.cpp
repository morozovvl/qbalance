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
    dictionaryName = dictName.trimmed().toLower();
    tagName = "saldo" + cAcc;
    quan = false;
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
}


QString Saldo::transformSelectStatement(QString statement) {
    QString command = statement;
    QString appendString = QString(" %1 сальдо.%2='%3' AND сальдо.%4=%5.%6").arg(command.contains("WHERE", Qt::CaseInsensitive)?"AND":"WHERE")
                                                                              .arg(db->getObjectName("счет.счет"))
                                                                              .arg(account)
                                                                              .arg(db->getObjectName("счет.код"))
                                                                              .arg(dictionaryName)
                                                                              .arg(db->getObjectName(dictionaryName + ".код"));
    if (quan)
        appendString.append(QString(" AND (сальдо.%1<>0 OR сальдо.%2<>0)").arg(db->getObjectName("сальдо.конкол"))
                                                                          .arg(db->getObjectName("сальдо.консальдо")));

    if (command.contains("ORDER BY", Qt::CaseInsensitive))
        command.replace(QString("ORDER BY"), appendString + " ORDER BY", Qt::CaseInsensitive);
    else
        command.append(appendString);
    command.replace(" FROM", QString(", сальдо.%1, сальдо.%2, сальдо.%3 FROM").arg(db->getObjectName("сальдо.конкол"))
                                                                              .arg(db->getObjectName("сальдо.концена"))
                                                                              .arg(db->getObjectName("сальдо.консальдо")), Qt::CaseInsensitive);
    command.replace(" WHERE", ", сальдо WHERE", Qt::CaseInsensitive);
    return command;
}


bool Saldo::open(int deep) {
    bool result = Dictionary::open(deep);
    lIsSet = false;                              // Сальдо не может быть набором
    formTitle = QString(QObject::trUtf8("Остатки на %1 счете").arg(account));
    QList<FieldType> saldoFields;
    QString salTableName = db->getObjectName("сальдо");
    db->getColumnsProperties(&saldoFields, salTableName);
    for (int i = 0; i < saldoFields.count(); i++)
    {
        if ((QString(saldoFields.at(i).name).compare("конкол",    Qt::CaseInsensitive) == 0) ||
            (QString(saldoFields.at(i).name).compare("концена",   Qt::CaseInsensitive) == 0) ||
            (QString(saldoFields.at(i).name).compare("консальдо", Qt::CaseInsensitive) == 0))
        {
            db->addColumnProperties(&columnsProperties, salTableName, saldoFields.at(i).name, saldoFields.at(i).type, saldoFields.at(i).length, saldoFields.at(i).precision, saldoFields.at(i).readOnly, saldoFields.at(i).constReadOnly);
        }
    }
    return result;
}
