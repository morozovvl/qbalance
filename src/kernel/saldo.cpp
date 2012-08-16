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
    //configName = "saldo" + cAcc;
    account = cAcc;
    dictionaryName = dictName;
    tagName = "saldo" + cAcc;
    quan = false;
    QSqlRecord accRecord = db->getAccountRecord(cAcc);
    quan = accRecord.value("количество").toBool();
}


QString Saldo::transformSelectStatement(QString statement) {
    QString command = statement;
    QString appendString = QString(" %1 сальдо.счет='%2' AND сальдо.код=%3.код%4").arg(command.contains("WHERE", Qt::CaseInsensitive)?"AND":"WHERE").arg(account).arg(dictionaryName).arg(quan?" AND (сальдо.конкол<>0 OR сальдо.консальдо<>0)":"");
    if (command.contains("ORDER BY", Qt::CaseInsensitive))
        command.replace(QString("ORDER BY"), appendString + " ORDER BY", Qt::CaseInsensitive);
    else
        command.append(appendString);
    command.replace(" FROM", ", сальдо.конкол, сальдо.концена, сальдо.консальдо FROM", Qt::CaseInsensitive);
    command.replace(" WHERE", ", сальдо WHERE", Qt::CaseInsensitive);
    return command;
}


bool Saldo::open(int deep) {
    bool result = Dictionary::open(deep);
    lIsSet = false;                              // Сальдо не может быть набором
    formTitle = QString(QObject::trUtf8("Остатки на %1 счете").arg(account));
    QList<FieldType> saldoFields;
    db->getColumnsProperties(&saldoFields, "сальдо");
    for (int i = 0; i < saldoFields.count(); i++)
    {
        if ((QString(saldoFields.at(i).name).compare("конкол",    Qt::CaseInsensitive) == 0) ||
            (QString(saldoFields.at(i).name).compare("концена",   Qt::CaseInsensitive) == 0) ||
            (QString(saldoFields.at(i).name).compare("консальдо", Qt::CaseInsensitive) == 0))
        {
            db->addColumnProperties(&columnsProperties, saldoFields.at(i).name, saldoFields.at(i).type, saldoFields.at(i).length, saldoFields.at(i).precision, saldoFields.at(i).readOnly);
        }
    }
    return result;
}
