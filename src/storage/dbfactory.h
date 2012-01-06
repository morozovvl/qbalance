#ifndef DBFACTORY_H
#define DBFACTORY_H

#include <QObject>
#include <QtSql>
#include <QDate>
#include <QVariantList>
#include <QByteArray>
#include <QList>
//#include "mysqlrelationaltablemodel.h"
//#include "../kernel/dictionary.h"

class TApplication;
class MySqlRelationalTableModel;
class Dictionary;

enum FileType           // Типы данных, которые хранятся в таблице "файлы"
{
    ScriptFileType,
    ReportTemplateFileType,
    PictureFileType
};


struct FieldType
{
    QString name;
    QString type;
    int length;
    int precision;
    bool readOnly;
    QString header;
    int number;
};


struct DictType
{
    QString name;       // Исходное наименование справочника
    QString prefix;     // Префикс "дб" или "кр"
    QString acc;        // на случай, если справочником будет сальдо, то здесь будет номер счета
    bool    isConst;
};


struct ToperType
{
    int         number;         // Порядковый номер проводки в типовой операции
    QString     dbAcc;          // Дебетовый счет
    QString     dbDict;         // Имя дебетового справочника
    QString     dbDictAlias;    // Псевдоним дебетового справочника в списке справочников
    bool        dbQuan;         // По дебетовому счету ведется количественный учет
    bool        dbConst;        // Дебетовый справочник является постоянным
    bool        dbSaldoVisible; // Сальдо по дебетовому справочнику видно
    bool        dbDictVisible;  // Дебетовый справочник видим
    QString     crAcc;          // Кредитовый счет
    QString     crDict;         // Имя кредитового справочника
    QString     crDictAlias;    // Псевдоним кредитового справочника в списке справочников
    bool        crQuan;         // По кредитовому счету ведется количественный учет
    bool        crConst;        // Кредитовый справочник является постоянным
    bool        crSaldoVisible; // Сальдо по кредитовому справочнику видно
    bool        crDictVisible;  // Кредитовый справочник видим
    QString     itog;           //
};


class DBFactory : public QObject {
    Q_OBJECT

public:
    DBFactory();
    virtual ~DBFactory() { ; }
    bool addDoc(int, QDate);
    bool removeDoc(int);
    bool addDocStr(int, int, QString cParam = "''", int nQuan = 1, int nDocStr = 0);
    bool removeDocStr(int, int);
    void clearError();
    bool createNewDB(QString, QString, int);
    QString getHostName() { return hostName; }
    QString getLogin() { return currentLogin; }
    QByteArray getFile(QString, FileType);
    void setFile(QString, FileType, QByteArray);
    int getPort() { return port; }
    Q_INVOKABLE QString getDatabaseName() { return dbName; }
    QSqlDatabase* getDB() { return db; }
    QSqlQuery getColumnsHeaders(QString);
    QSqlQuery getDictionariesProperties();
    QSqlRecord getDictionariesProperties(QString tableName);
    QSqlQuery getTopersProperties();
    QSqlRecord getTopersProperties(int operNumber);
    QSqlQuery getToper(int operNumber);
    int getTypeId(QString);
    int getDictionaryId(QString dictName);
    bool isTableExists(QString);
    bool createNewDictionary(QString, QString = "", bool = true);
    bool removeDictionary(QString);
    QStringList getFieldsList(QMap<int, FieldType>*);
    QStringList getFieldsList(QString tableName);
    void addColumnProperties(QMap<int, FieldType>*, QString, QString, int, int, bool readOnly = false, int number = 0);
    void getColumnsProperties(QMap<int, FieldType>*, QString);
    void getColumnsProperties(QList<FieldType>*, QString);
    void getColumnsRestrictions(QString, QMap<int, FieldType>*);
    QString getPhotoDatabase();
    bool insertDictDefault(QString tableName, QStringList fields = QStringList(), QVariantList values = QVariantList());// Вставляет в справочник новую строку со значениями по умолчанию
    bool removeDictValue(QString, qulonglong);                                          // Удаляет строку в указанном справочнике с заданным кодом
    void setHostName(QString name) { hostName = name; }
    void setPort(int portNum) { port = portNum; }
    void setDatabaseName(QString name) { dbName = name; }
    void setPeriod(QDate, QDate);
    void getPeriod(QDate&, QDate&);
    void setConstDictId(QString, QVariant, int, int, int);
    QString prepareSearchParameters();
    Q_INVOKABLE bool exec(QString);
    Q_INVOKABLE QSqlQuery execQuery(QString);
    QStringList getUserList();
    QString getPhotoPath(QString);
    QString getIdFieldPrefix() { return getObjectName("код_"); }      // возвращает префикс в именах полей, которые используются как ссылки на другие справочники

    bool isError() { return wasError; }
    QString getErrorText() { return errorText; }

    QString initializationScriptPath() const;
    QStringList initializationScriptList() const;

    QString getObjectName(const QString&) const;       // транслирует имена объектов БД из "внутренних" в реальные наименования

    static QString storageEncoding();

    virtual bool open();
    virtual bool open(QString, QString);
    void initDBFactory();

    virtual void close();

    void beginTransaction()     { exec("BEGIN;"); }
    void commitTransaction()    { exec("COMMIT;"); }
    void rollbackTransaction()  { exec("ROLLBACK;"); }

    QSqlQuery getDataTypes();

    void getToperData(int oper, QList<ToperType>* topersList);
    void setToperDictAliases(QList<ToperType>* topersList, QMap<QString, DictType>* dictsList);

    QString getDocumentSqlSelectStatement(int oper,
                                          QList<ToperType>*,
                                          QMap<int, FieldType>* = 0,
                                          int * = 0);     // Генерирует текст SQL-запроса для табличной части документа операции oper
    QSqlQuery getAccountRecord(QString cAcc);

    // Функции для мастера создания новых (свойств старых) справочников
    bool setTableGuiName(QString tableName, QString menuName, QString formName);
    bool addTableColumn(QString, QString, QString);
    bool dropTableColumn(QString, QString);
    bool renameTableColumn(QString, QString, QString);
    bool alterTableColumn(QString, QString, QString);
    bool appendColumnHeader(int, QString, QString, int = 999);
    bool updateColumnHeader(int, QString, QString, int = 0);
    bool setTableColumnHeaderOrder(int, QString, QString, int);
    bool deleteToper(int operNumber);
    bool addToperPrv(int operNumber, QString name, QString dbAcc, bool dbAccConst, QString crAcc, bool crAccConst, QString itog);
    int getNewToper();
    bool createNewToperPermission(QString, bool);


private:
    QSqlDatabase*           db;
    QSqlQuery               objectTypes;
    QString                 hostName;           // URL сервера
    int                     port;               // порт сервера
    QString                 currentLogin;       // логин, под которым работает пользователь
    QString                 dbName;             // наименование базы, с которой работает пользователь
    bool                    wasError;           // во время обращения к БД произошла ошибка
    QString                 errorText;          // текст последней ошибки
    QMap<QString, QString>  ObjectNames;        // таблица для трансляции имен полей, таблиц, просмотров, функций из наименований ядра в наименования БД

    void setError(QString);
    void initObjectNames();
};

#endif
