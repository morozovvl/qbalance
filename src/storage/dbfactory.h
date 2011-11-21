#ifndef DBFACTORY_H
#define DBFACTORY_H

#include <QObject>
#include <QtSql>
#include <QDate>
#include <QVariantList>
#include <QByteArray>
#include <QList>

class TApplication;


enum FileType           // Типы данных, которые хранятся в таблице "файлы"
{
    Script,
    ReportTemplate
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
    int getPort() { return port; }
    Q_INVOKABLE QString getDatabaseName() { return dbName; }
    QSqlDatabase* getDB() { return db; }
    QSqlQuery getColumnsHeaders(QString);
    QSqlQuery getDictionariesProperties();
    int getDictionaryTypeId();
    bool isTableExists(QString);
    bool createNewDictionary(QString, QString = "", bool = true);
    bool removeDictionary(QString);
    void renameTableColumn(QString, QString, QString);
    void alterTableColumn(QString, QString, QString);
    void addTableColumn(QString, QString, QString);
    void dropTableColumn(QString, QString);
    void appendColumnHeader(QString, QString, QString);
    void updateColumnHeader(QString, QString, QString);
    void setTableColumnHeaderOrder(QString, QString, int);
    QStringList getFieldsList(QMap<int, FieldType>*);
    void addColumnProperties(QMap<int, FieldType>*, QString, QString, int, int, bool readOnly = false);
    void getColumnsProperties(QMap<int, FieldType>*, QString);
    void getColumnsProperties(QList<FieldType>*, QString);
    void getColumnsRestrictions(QString, QMap<int, FieldType>*);
    QSqlQuery getTopersProperties();
    QSqlQuery getToper(int);
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
    virtual void close();

    void beginTransaction()     { exec("BEGIN;"); }
    void commitTransaction()    { exec("COMMIT;"); }
    void rollbackTransaction()  { exec("ROLLBACK;"); }

    QSqlQuery getDataTypes();

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
