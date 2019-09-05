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
#include <QtCore/QProcess>
#include <QtCore/QPointer>
#include <QtSql/QSqlQuery>

#include "mysqlrelationaltablemodel.h"
#include "filetype.h"
#include "mymultilist.h"


class TApplication;
class Dictionary;
class Dictionaries;


struct FileInfo
{
    int   size;
    QDateTime   lastModified;
};


struct UserInfo
{
    int         id;
    QString     userName;
    QString     loginName;
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


struct ColumnPropertyType
{
    QString     name;
    QString     type;
    int         length;
    int         precision;
    QString     updateable;
};


class DBFactory : public QObject {
    Q_OBJECT

public:
    DBFactory();
    ~DBFactory();

    // Работа с соединением к БД
    int getPort();
    QString getHostName();
    virtual QString getLogin();
    virtual QString getConnectionName() { return ""; }
    void setHostName(QString name);
    void setPort(int portNum);
    virtual int openDBDialog();

    // Создание и открытие БД
    virtual bool open();
    virtual bool open(QString, QString);
    virtual void close();
    bool isOpened();
    virtual void initDBFactory();
    bool createNewDBs(QString, QString, int);

    // Работа с базой
    void setDatabaseName(QString name);
    QString getDatabaseName();
    QSqlDatabase* getDB();

    // Работа со справочниками
    virtual bool createNewDictionary(QString, QString = "", bool = true);
    virtual QSqlQuery getDictionariesProperties();
    virtual QSqlRecord getDictionariesProperties(QString tableName);
    virtual QString getDictionariesProperties(QString, QString);
    int getDictionaryId(QString dictName);
    bool removeDictionary(QString);
    Q_INVOKABLE QString getDictionaryPhotoPath(QString);
    void reloadDictionariesPermitions();
    virtual int insertDictDefault(QString, QHash<QString, QVariant>*) { return -1; }                 // Вставляет в справочник новую строку
    bool removeDictValue(QString, int);                                          // Удаляет строку в указанном справочнике с заданным кодом
    void setConstDictId(QString, QVariant, int, int, int);


    // Работа с бухгалтерскими документами
    Q_INVOKABLE virtual bool    lockDocument(int) { return true; }
    Q_INVOKABLE virtual void    unlockDocument(int) {;}
    virtual void    clearLockedDocumentList() {;}

    virtual int addDoc(int, QDate);                                                             // Создать новый документ по типовой операции operNumber с датой date
    Q_INVOKABLE virtual void removeDoc(int);                                                    // Удалить документ с идентификатором docId
    virtual int addDocStr(int, int, QString = "''", int = 1, int = 0);    // Добавить новую строку в документ по типовой операции operNumber
                                                                                                        // с идентификатором docId. В строке cParam через запятую находится информация об идентификаторах объектов учета,
                                                                                                        // их количестве, цене и сумме или строка cParam может быть пустой
                                                                                                        // nQuan - сколько строк вставить, nDocStr - вставить строку с номером
    virtual bool removeDocStr(int, int);                                                          // Удалить строку в документе docId под номером nDocStr
    void saveDocAttribute(int, int, QString);
    QSqlQuery getDocumentAddQueriesList(int);

    QSqlQuery getToper(int);
    QVariant getTopersProperties(int, QString);

    void getToperData(int oper, QList<ToperType>* topersList);
    void getToperDictAliases(int oper, QList<ToperType>* topersList, QList<DictType>* dictsList);
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

    // Работа с файлами (скриптами, формами, картинками и т.п.)
    QByteArray getFile(QString, int, bool = false);        // Получить файл из базы. Если последний параметр Истина, то получить из расширенной базы
    qulonglong getFileCheckSum(QString, FileType, bool = false);
    FileInfo getFileInfo(QString, FileType, bool = false);
    QStringList getFilesList(QString, FileType, bool = false);
    bool isFileExist(QString, FileType, bool = false);
    void removeFile(QString, FileType, bool = false);
    virtual void setFile(QString, FileType, QByteArray, bool = false) = 0;
    void copyFile(QString, QString, bool = false);


    virtual void getColumnsHeaders(QString, QList<FieldType>*);
    QStringList getFieldsList(QHash<int, FieldType>*);
    QStringList getFieldsList(QString tableName, int = -1);
    bool isSet(QString tableName);
    virtual void getColumnsProperties(QList<FieldType>*, QString = "", QString = "", int = 0);
    void getColumnsRestrictions(QString, QList<FieldType>*);                    // Устанавливает ограничение на просматриваемые поля исходя из разграничений доступа
    QString getPhotoDatabase();
    void insertSaldo(QString , int);                 // Вставляет в сальдо новую строку
    void setPeriod(QDate, QDate);
    virtual bool getPeriod(QDate&, QDate&);
    QHash<int, UserInfo> getUserList();

    // Работа с ошибками
    Q_INVOKABLE virtual bool exec(QString = "", bool = true, QSqlDatabase* = nullptr);
    Q_INVOKABLE void exec(QStringList);
    Q_INVOKABLE bool execQueryFile(QString, bool = true);
    bool execSystem(QString command, QString tableName);       // Будет вызываться там, где необходима проверка изменения системных таблиц
    Q_INVOKABLE virtual QSqlQuery execQuery(QString, bool = true, QSqlDatabase* = nullptr) = 0;

    Q_INVOKABLE virtual QString getObjectName(const QString&);       // транслирует имена объектов БД из "внутренних" в реальные наименования
    Q_INVOKABLE virtual QString getObjectNameCom(const QString&);                        // то же самое, только результат возвращает в кавычках (применяется при генерации SQL команд)

    Q_INVOKABLE bool beginTransaction();
    Q_INVOKABLE void commitTransaction();
    Q_INVOKABLE void rollbackTransaction();

    virtual void loadSystemTables();

    QSqlQuery getAccounts();
    QVariant getAccountsValue(QString, QString);

    // Функции для сохранения в базе и восстановления конфигураций объектов
    virtual void setConfig(QString, QString, QString);
    virtual void getConfig(QString, QHash<QString, int> *);


    // Функции для мастера создания новых (свойств старых) справочников
    bool setTableGuiName(QString tableName, QString menuName, QString formName);
    bool addTableColumn(QString, QString, QString);
    bool dropTableColumn(QString, QString);
    bool renameTableColumn(QString, QString, QString);
    bool alterTableColumn(QString, QString, QString);
    bool appendColumnHeader(int, int, QString, QString, int, bool);
    bool removeColumnHeaders(int);

    Q_INVOKABLE bool isTableExists(QString);
    bool isView(QString);


    Q_INVOKABLE bool    execCommands();
    Q_INVOKABLE void    clearCommands();
    bool    isExistsCommands();
    Q_INVOKABLE void    appendCommand(QString);
    void    appendCommand(UpdateValues);
    Q_INVOKABLE void    prepareCommands();
    Q_INVOKABLE QStringList getCommands();

    Q_INVOKABLE virtual QVariant getValue(QString command, int row, int column);
    Q_INVOKABLE virtual QVariant getValue(QString command, int row, QString column);
    Q_INVOKABLE virtual QVariant getValue(QString command);
    Q_INVOKABLE virtual QSqlRecord getRecord(QString command, int row);
    Q_INVOKABLE virtual QVariant getOstSum(QString acc, int id = 0);     // Получить сумму остатка на счете для объекта
    Q_INVOKABLE virtual int getInsertReturningId(QString, QString, QString) { return 0; }
    Q_INVOKABLE QString driverName();

    void changePassword(QString);

    virtual void saveUpdate(QString);
    virtual void loadUpdates();
    virtual int updatesCount();
    virtual int getErrorNumber();

    void    clearUpdateNum();
    void addColumnProperties(QList<FieldType>*, QString, QString, QString, int, int, bool = false, bool = false, int = 0, int = 0);
    virtual int getSecDiff();
    virtual QString getILIKEexpression(QString, QString) { return ""; }       // Возвращает аналог выражения ILIKE для разных БД
    QString getDictPrototype(QString);
    virtual QDate toDate(QVariant) = 0;

    virtual QString getTrueValue();
    virtual QString getFalseValue();
    virtual QString getCurrentTimeStamp();

    virtual int querySize(QSqlQuery*) = 0;

protected:
    TApplication*           app;
    QSqlDatabase*           db;
    QSqlDatabase*           dbExtend;
    int                     pid;
    bool                    extDbExist;         // Расширенная ДБ существует
    QSqlQuery               objectTypes;
    QSqlQuery               dictionariesPermitions;     // Таблица доступа к справочникам
    QSqlQuery               columnsHeaders;
    QSqlQuery               config;
    QSqlQuery               accounts;
    QSqlQuery               columnsRestrictions;
    QSqlQuery               files;
    QString                 hostName;           // URL сервера
    int                     port;               // порт сервера
    QString                 currentLogin;       // логин, под которым работает пользователь
    QString                 currentPassword;    // пароль, под которым работает пользователь
    QString                 dbName;             // наименование базы, с которой работает пользователь
    bool                    wasError;           // во время обращения к БД произошла ошибка
    QString                 errorText;          // текст последней ошибки
    QHash<QString, QString>  ObjectNames;        // таблица для трансляции имен полей, таблиц, просмотров, функций из наименований ядра в наименования БД
    QStringList             commands;
    QStringList             sysTables;
    QHash<QString, QString> tables;
    QStringList             dbUpdatesList;
    QList<UpdateValues>     updateValues;
    bool                    dbIsOpened;
    int                     updateNum;
    QPointer<QProcess>      proc;
    int                     errorNumber;
    int                     secDiff;
    QHash<QString, QString>   dictsPrototypes;
//    QMultiMap<QString, ColumnPropertyType>  columnsProperties;
    MyMultiList<ColumnPropertyType>  columnsProperties;

    void setError(QString);
    void initObjectNames();
    bool createNewDB(QString, QString, QStringList);
    static QString storageEncoding();
    QStringList initializationScriptList(QString = "") const;
    int getTypeId(QString);
    void clearError();
    bool execPSql(QStringList command, QString user, QString password);
    virtual void reloadColumnProperties() = 0;
    virtual void reloadColumnHeaders();

private slots:
    void showPSqlMessage();
};

#endif
