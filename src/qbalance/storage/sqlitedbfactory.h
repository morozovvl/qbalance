#ifndef SQLITEDBFACTORY_H
#define SQLITEDBFACTORY_H
#include "dbfactory.h"


class SQLiteDBFactory : public DBFactory
{
public:
    SQLiteDBFactory();

    virtual bool open(QString = "", QString = "");
    virtual int openDBDialog();
    virtual QString getLogin();

    virtual QString getConnectionName();
    virtual void loadSystemTables();
    virtual void getColumnsProperties(QList<FieldType>*, QString = "", QString = "", int = 0);

    virtual int insertDictDefault(QString, QHash<QString, QVariant>*);                 // Вставляет в справочник новую строку
    virtual QString getILIKEexpression(QString, QString);

    virtual bool getPeriod(QDate&, QDate&);

    virtual bool createNewDictionary(QString, QString = "", bool = true);

    virtual QString getTrueValue();
    virtual QString getFalseValue();

    virtual int addDoc(int, QDate = QDate::currentDate());       // Создать новый документ по типовой операции operNumber с датой date
    virtual void removeDoc(int);                                 // Удалить документ с идентификатором docId
    virtual int addDocStr(int, int, QString = "", int = 1, int = 0);    // Добавить новую строку в документ по типовой операции operNumber

    virtual QString getCurrentTimeStamp();

    Q_INVOKABLE virtual int getInsertReturningId(QString, QString, QString);

    virtual void setFile(QString, FileType, QByteArray, bool = false);
};

#endif // SQLITEDBFACTORY_H
