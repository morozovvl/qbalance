#include "saldo.h"
#include "../kernel/app.h"
#include "../storage/mysqlrelationaltablemodel.h"

Saldo::Saldo(QString cAcc, QString dictName, QObject *parent)
: Dictionary(dictName, parent) {
    //configName = "saldo" + cAcc;
    account = cAcc;
    dictionaryName = dictName;
    tagName = "saldo" + cAcc;
    quan = false;
    QSqlRecord accRecord = TApplication::exemplar()->getDBFactory()->getAccountRecord(cAcc);
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

void Saldo::setLock(bool lock) {
    Dictionary* dict = dictionaries->getDictionary(dictionaryName);
    dict->setId(getId());
    Dictionary::setLock(lock);
}

void Saldo::setMustShow(bool mustShow) {
    Dictionary* dict = dictionaries->getDictionary(dictionaryName);
    dict->setMustShow(mustShow);
    Dictionary::setMustShow(mustShow);
}

bool Saldo::open(int deep) {
    bool result = Dictionary::open(deep);
    formTitle = QString(QObject::trUtf8("Остатки на %1 счете").arg(account));
    QMap<int, FieldType> saldoFields;
    TApplication::exemplar()->getDBFactory()->getColumnsProperties(&saldoFields, "сальдо");
    foreach (int i, saldoFields.keys())
    {
        if ((QString(saldoFields.value(i).name).compare("конкол",    Qt::CaseInsensitive) == 0) ||
            (QString(saldoFields.value(i).name).compare("концена",   Qt::CaseInsensitive) == 0) ||
            (QString(saldoFields.value(i).name).compare("консальдо", Qt::CaseInsensitive) == 0))
        {
            TApplication::exemplar()->getDBFactory()->addColumnProperties(&columnsProperties, saldoFields.value(i).name, saldoFields.value(i).type, saldoFields.value(i).length, saldoFields.value(i).precision, saldoFields.value(i).readOnly);
        }
    }
    return result;
}
