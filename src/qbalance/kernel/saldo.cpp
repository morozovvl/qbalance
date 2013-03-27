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
    lIsSet = false;                              // Сальдо не может быть набором
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


bool Saldo::open(int deep)
{
    if (Dictionary::open(deep))
    {
        fieldList = getFieldsList();
        int columnCount = fieldList.count();

        QString salTableName = db->getObjectName("сальдо");
        QList<FieldType> saldoFields;
        db->getColumnsProperties(&saldoFields, salTableName);

        tableModel->setRelation(0, QSqlRelation(salTableName, idFieldName, idFieldName));

        for (int i = 0; i < saldoFields.count(); i++)
        {
            if ((QString(saldoFields.at(i).name).compare("конкол",    Qt::CaseInsensitive) == 0) ||
                (QString(saldoFields.at(i).name).compare("концена",   Qt::CaseInsensitive) == 0) ||
                (QString(saldoFields.at(i).name).compare("консальдо", Qt::CaseInsensitive) == 0))
            {
                QString columnName = salTableName.toUpper() + "__" + saldoFields.at(i).name.toUpper();
                tableModel->insertColumns(columnCount, 1);
                tableModel->setRelation(columnCount, 0, QSqlRelation(salTableName, idFieldName, saldoFields.at(i).name.toUpper()));
                tableModel->setHeaderData(columnCount, Qt::Horizontal, QVariant(columnName));
                db->addColumnProperties(&columnsProperties, salTableName, columnName, saldoFields.at(i).type, saldoFields.at(i).length, saldoFields.at(i).precision, saldoFields.at(i).readOnly, saldoFields.at(i).constReadOnly);
                columnCount++;
            }
        }

        // Установим порядок сортировки и стратегию сохранения данных на сервере
//        tableModel->setSort(tableModel->fieldIndex(db->getObjectName("имя")), Qt::AscendingOrder);
        db->getColumnsRestrictions(tableName, &columnsProperties);
        initForm();
        initFormEvent();
        return true;
    }
    app->getGUIFactory()->showError(QString(QObject::trUtf8("Запрещено просматривать справочник <%1> пользователю %2. Либо справочник отсутствует.")).arg(formTitle, TApplication::exemplar()->getLogin()));
    return false;

}


QString Saldo::transformSelectStatement(QString statement) {
    QString command = statement;
    QString appendString = QString(" %1 сальдо.%2='%3'").arg(command.contains("WHERE", Qt::CaseInsensitive)?"AND":"WHERE")
                                                                            .arg(db->getObjectName("счет.счет"))
                                                                            .arg(account);
    if (quan)
        appendString.append(QString(" AND (сальдо.%1<>0 OR сальдо.%2<>0)").arg(db->getObjectName("сальдо.конкол"))
                                                                         .arg(db->getObjectName("сальдо.консальдо")));
    if (command.contains("ORDER BY", Qt::CaseInsensitive))
        command.replace(QString("ORDER BY"), appendString + " ORDER BY", Qt::CaseInsensitive);
    else
        command.append(appendString);
    return command;
}


