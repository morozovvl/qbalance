#include "saldo.h"
#include "../gui/app.h"
#include "../storage/mysqlrelationaltablemodel.h"

Saldo::Saldo(QString cAcc, QString dictName, QObject *parent)
: Dictionary(dictName, parent) {
    //configName = "saldo" + cAcc;
    account = cAcc;
    dictionaryName = dictName;
    tagName = "saldo" + cAcc;
    quan = false;
    QSqlQuery accRecord = TApplication::exemplar()->getDBFactory()->execQuery(QString("SELECT количество FROM счета WHERE счет LIKE '%1'").arg(cAcc));
    if (accRecord.first())
       quan = accRecord.record().value("количество").toBool();
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
    formTitle = QString(QObject::tr("Остатки на %1 счете").arg(account));
    return result;
}
