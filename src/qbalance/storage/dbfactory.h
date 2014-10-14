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

#ifndef DBFACTORY_H
#define DBFACTORY_H

#include <QtCore/QObject>
#include <QtCore/QDate>
#include <QtCore/QVariantList>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QTextStream>
#include <QtCore/QDateTime>
#include <QtCore/QHash>

#include "mysqlrelationaltablemodel.h"


class TApplication;
class Dictionary;
class Dictionaries;

enum FileType           // Типы данных, которые хранятся в таблице "файлы"
{
    ScriptFileType,
    ReportTemplateFileType,
    PictureFileType,
    FormFileType
};


struct FileInfo
{
    qlonglong   size;
    QDateTime   lastModified;
};


struct FieldType
{
    QString table;          // Наименование таблицы
    QString name;           // Наименование поля таблицы
    QString column;         // Синтетическое наименование поля таблицы (<имя таблицы>__<имя поля>)
    QString type;           // Тип поля таблицы
    int length;             // Длина поля
    int precision;          // Точность (если numeric)
    bool readOnly;          // Только для чтения (установлено пользователем)
    bool constReadOnly;     // Системное поле. Поэтому только для чтения
    QString header;         // Пользовательский заголовок
    bool headerExist;       // Используется для внутренних целей поиска заголовка
    int number;             // Порядковый номер при отображении столбца
    int level;              // Уровень таблицы. Для базовой таблицы уровень = 0, для связанных таблиц уровень повышается. Используется для внутренних целей
};


struct DictType
{
    QString name;       // Исходное наименование справочника
    QString acc;
    QString prototype;  // Справочник - прототип - справочник, который является основой для этого справочника и коды позиций в которых совпадают
    bool    isSaldo;
    bool    isConst;
    bool    isSet;
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
    QString     crAcc;          // Кредитовый счет
    QString     crDict;         // Имя кредитового справочника
    QString     crDictAlias;    // Псевдоним кредитового справочника в списке справочников
    bool        crQuan;         // По кредитовому счету ведется количественный учет
    bool        crConst;        // Кредитовый справочник является постоянным
    bool        crSaldoVisible; // Сальдо по кредитовому справочнику видно
    bool        isSingleString; // В документе должна быть только одна строка
    QString     itog;           //
    bool        freePrv;        // Свободная проводка
    bool        attributes;     // Наличие дополнительных атрибутов (полей) в табличной части документов
    bool        docattributes;  // Наличие дополнительных атрибутов у самого документа
};


struct UpdateValues
{
    QString     table;
    QString     field;
    QString     value;
    int         recId;
};


struct UpdateIds
{
    int         id;
    QString     table;
};

class DBFactory : public QObject {
    Q_OBJECT

public:
    DBFactory();
    ~DBFactory();

    virtual bool open();
    virtual bool open(QString, QString);
    virtual void close();
    void initDBFactory();
    bool createNewDBs(QString, QString, int);

    // Работа с документами
    int addDoc(int, QDate);
    bool removeDoc(int);
    int addDocStr(int, int, QString cParam = "''", int nQuan = 1, int nDocStr = 0);
    bool removeDocStr(int, int);
    void saveDocAttribute(int, int, QString, QVariant);
    void saveDocumentVariables(int docId, QString xml);
    QString restoreDocumentVariables(int docId);
    QSqlQuery getDocumentAddQueriesList(int);
    QSqlRecord getDocumentAddQuery(int);

    // Работа с файлами
    QByteArray getFile(QString, FileType, bool = false);        // Получить файл из базы. Если последний параметр Истина, то получить из расширенной базы
    qulonglong getFileCheckSum(QString, FileType, bool = false);
    QStringList getFilesList(QString, FileType, bool = false);
    virtual bool isFileExist(QString, FileType, bool = false);
    void setFile(QString, FileType, QByteArray, bool = false);
    static qulonglong calculateCRC32(QByteArray*);

    // Работа с соединением
    int getPort() { return port; }
    QString getHostName() { return hostName; }
    QString getLogin() { return currentLogin; }
    void setHostName(QString name) { hostName = name; }
    void setPort(int portNum) { port = portNum; }

    // Работа с базой
    void setDatabaseName(QString name) { dbName = name; }
    QString getDatabaseName() { return dbName; }
    QSqlDatabase* getDB() { return db; }

    virtual void getColumnsHeaders(QString, QList<FieldType>*);
    QSqlQuery getDictionariesProperties();
    virtual QSqlRecord getDictionariesProperties(QString tableName);
    QSqlQuery getTopersProperties();
    QSqlRecord getTopersProperties(int operNumber);
    QSqlQuery getToper(int operNumber);
    int getDictionaryId(QString dictName);
    bool removeDictionary(QString);
    QStringList getFieldsList(QMap<int, FieldType>*);
    QStringList getFieldsList(QString tableName, int = -1);
    bool isSet(QString tableName);
    void getColumnsProperties(QList<FieldType>*, QString = "", QString = "", int = 0);
    void getColumnsRestrictions(QString, QList<FieldType>*);                    // Устанавливает ограничение на просматриваемые поля исходя из разграничений доступа
    QString getPhotoDatabase();
    int insertDictDefault(QString tableName, QMap<QString, QVariant>* values);                 // Вставляет в справочник новую строку
    bool removeDictValue(QString, qulonglong);                                          // Удаляет строку в указанном справочнике с заданным кодом
    void setPeriod(QDate, QDate);
    void getPeriod(QDate&, QDate&);
    void setConstDictId(QString, QVariant, int, int, int);
    QStringList getUserList();
    Q_INVOKABLE QString getDictionaryPhotoPath(QString);

    // Работа с ошибками
    Q_INVOKABLE bool exec(QString, bool = true, QSqlDatabase* = 0);
    Q_INVOKABLE QSqlQuery execQuery(QString, bool = true, QSqlDatabase* = 0);

    Q_INVOKABLE virtual QString getObjectName(const QString&);       // транслирует имена объектов БД из "внутренних" в реальные наименования
    Q_INVOKABLE virtual QString getObjectNameCom(const QString&);                        // то же самое, только результат возвращает в кавычках (применяется при генерации SQL команд)

    void beginTransaction();
    void commitTransaction();
    void rollbackTransaction();

    void loadSystemTables();

    void getToperData(int oper, QList<ToperType>* topersList);
    void getToperDictAliases(int oper, QList<ToperType>* topersList, QList<DictType>* dictsList);

    QString getDocumentSqlSelectStatement(int oper,
                                          QList<ToperType>*,
                                          QList<FieldType>* = 0,
                                          int * = 0);     // Генерирует текст SQL-запроса для табличной части документа операции oper
    QString getDictionarySqlSelectStatement(QString, QString = "");       // Генерирует текст SQL-запроса для справочника
    QSqlQuery getAccounts() { return accounts; }

    // Функции для сохранения в базе и восстановления конфигураций объектов
    void setConfig(QString, QString, QString);
    QSqlQuery getConfig() { return config; }

    // Функции для мастера создания новых (свойств старых) справочников
    bool setTableGuiName(QString tableName, QString menuName, QString formName);
    bool addTableColumn(QString, QString, QString);
    bool dropTableColumn(QString, QString);
    bool renameTableColumn(QString, QString, QString);
    bool alterTableColumn(QString, QString, QString);
    bool appendColumnHeader(int, int, QString, QString, int, bool);
    bool removeColumnHeaders(int);
    void reloadDictionariesPermitions();
    void reloadColumnHeaders();
    void reloadColumnProperties();
    QSqlQuery* getDictionaries() { return &dictionaries; }

    // Функции для мастера работы со справочниками
    bool createNewDictionary(QString, QString = "", bool = true);
    bool isTableExists(QString);


    // Функции для мастера создания новый (редактирования старых) типовых операций
    bool deleteToper(int operNumber, int operNumber1);          // Удаляет записи о типовой операции в таблице типовых операций
    bool deleteAllToperInfo(int operNumber);                    // Удаляет всю информацию о типовой операции, если по ней уже не созданы документы
    bool addToperPrv(int operNumber,                            // Создает новую проводку для заданной типовой операции
                     int operNumber1,
                     QString name,
                     QString dbAcc,
                     bool dbAccConst,
                     bool dbVisible,
                     bool dbSalVisible,
                     QString crAcc,
                     bool crAccConst,
                     bool crVisible,
                     bool crSalVisible,
                     QString itog,
                     bool freePrv,
                     bool attribute);
    int getNewToper();                                          // Получает свободный номер для новой типовой операции
    bool getToperSingleString(int);                             // Получает значение флага "одна строка в документе" для типовой операции
    bool setToperSignleString(int, bool);                       // Устанавливает значение флага "одна строка в документе" для типовой операции
    QString getToperNumerator(int);                             // Получает значение свойства "нумератор" типовой операции
    bool setToperNumerator(int, QString);                       // Устанавливает значение свойства "нумератор" типовой операции
    void setToperPermition(int operNumber, QString user, bool menu);
    bool    execCommands();
    void    clearCommands();
    bool    isExistsCommands();
    void    appendCommand(QString);
    void    appendCommand(UpdateValues);


private:
    QSqlDatabase*           db;
    QSqlDatabase*           dbExtend;
    bool                    extDbExist;         // Расширенная ДБ существует
    QSqlQuery               objectTypes;
    QSqlQuery               dictionariesPermitions;     // Таблица доступа к справочникам
    QSqlQuery               columnsProperties;
    QSqlQuery               columnsHeaders;
    QSqlQuery               config;
    QSqlQuery               accounts;
    QSqlQuery               columnsRestrictions;
    QSqlQuery               files;
    QSqlQuery               dictionaries;
    QString                 hostName;           // URL сервера
    int                     port;               // порт сервера
    QString                 currentLogin;       // логин, под которым работает пользователь
    QString                 currentPassword;    // пароль, под которым работает пользователь
    QString                 dbName;             // наименование базы, с которой работает пользователь
    bool                    wasError;           // во время обращения к БД произошла ошибка
    QString                 errorText;          // текст последней ошибки
    QHash<QString, QString>  ObjectNames;        // таблица для трансляции имен полей, таблиц, просмотров, функций из наименований ядра в наименования БД
    QStringList             commands;
    QList<UpdateValues>     updateValues;

    void setError(QString);
    void initObjectNames();
    bool createNewDB(QString, QString, QStringList);
    static QString storageEncoding();
    QStringList initializationScriptList(QString = "") const;
    int getTypeId(QString);
    void clearError();
    void addColumnProperties(QList<FieldType>*, QString, QString, QString, int, int, bool = false, bool = false, int = 0);
};

#endif
