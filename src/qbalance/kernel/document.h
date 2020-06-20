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

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QtSql/QSqlTableModel>
#include <QtCore/QString>
#include <QtCore/QHash>
#include "dictionary.h"


class TApplication;
class Documents;
class Saldo;
class FormDocument;

struct ToperType;


struct prvSaldo {
    double  dbQuan;
    double  dbSaldo;
    double  crQuan;
    double  crSaldo;
};

class Document : public Dictionary {
    Q_OBJECT

private:
    QHash<QString, QVariant>         prvValues;          // Значения проводок для сохранения в БД из процедуры appendDocString
    QHash<QString, QVariant>         variables;          // Значения переменных, используемых в скриптах для восстановления или последующего сохранения в БД
    Documents*                      parent;
    int                             operNumber;
    int                             docId;
    int                             prv1;
    bool                            isSingleString;     // В документе должна присутствовать только одна строка (для платежных поручений, например)
    QList<QString>                  attrFields;         // Имена полей атрибутов документа, которые могут добавляться при добавлении новой строки
    QString                         selectStatement;
    QHash<QString, QVariant>        oldValues0;         // Старые значения для первой строки документа - там хранятся значения "свободной" проводки
    QList<ToperType>*               topersList;
    bool                            localDictsOpened;
    bool                            docModified;
    bool                            quanAccount;        // В проводках есть количественный учет
    bool                            singlePrv;          // Проводка простая (одиночная)
    bool                            addingFromQuery;

    bool showNextDict();
    void showItog();
    int     findFreePrv(int);              // Ищет строку, в которой отображена "свободная" проводка, т.к. она может быть и не в первой строке
    bool    isFreePrv(int);
    bool                            checkConstDicts();

protected:
    virtual void        preparePrintValues();           // Готовит значения для печати
    virtual void        prepareSelectCurrentRowCommand();
    virtual bool        setTableModel(int = 0);

    Document(int, Documents*);
    virtual void postInitialize(int, Documents*);

public:
    ~Document();

    template <class T>
        static T* create(int opNumber, Documents *parent = 0 /*nullptr*/)
        {
            T* p(new T(opNumber, parent));
            p->postInitialize(opNumber, parent);
            return p;
        }

    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();
    Q_INVOKABLE virtual bool add();
    Q_INVOKABLE virtual bool remove(bool = false);
    Q_INVOKABLE virtual int exec();                // Показать форму в немодальном режиме
    Q_INVOKABLE virtual void show();                // Показать форму в немодальном режиме
    Q_INVOKABLE virtual void hide();                // Скрыть форму
    Q_INVOKABLE virtual void query();
    Q_INVOKABLE virtual void cmdOk();                       // Обработка нажатий кнопок "Ok"



    Q_INVOKABLE int getDocId();
    Q_INVOKABLE int getOperNumber();
    int             getPrvQuan();
    Documents* getParent();
    QHash<QString, Dictionary*>* getDictionariesList();
    Dictionaries* getDocDictionaries();
    Q_INVOKABLE Dictionary* getDictionary(QString dictName);
    Q_INVOKABLE Saldo* getSaldo(QString acc);
    virtual void             load();

    virtual QString transformSelectStatement(QString string);
    void setDocId(int doc);
    Q_INVOKABLE virtual bool calculate(bool = true);
    virtual void setConstDictId(QString, QVariant);
    virtual void setScriptEngine();
    int    addFromQuery(QString);
    DocumentScriptEngine* getScriptEngine();
    bool getIsSingleString();
    Q_INVOKABLE void setDate(QString);
    Q_INVOKABLE QString getDate();
    Q_INVOKABLE void setNumber(QString);
    Q_INVOKABLE QString getNumber();
    Q_INVOKABLE void showParameterText(QString);
    Q_INVOKABLE int appendDocString(bool = true);
    Q_INVOKABLE int appendDocStrings(int);
    void prepareValue(QString, Dictionary*);
    Q_INVOKABLE void prepareValue(QString, QVariant);
    Q_INVOKABLE virtual void setValue(QString name, QVariant value, int row = -1);
    Q_INVOKABLE virtual void setValue(int, QString name, QVariant value, int row = -1);
    Q_INVOKABLE virtual QVariant getValue(QString, int row = -1);
    Q_INVOKABLE virtual QVariant getValue(int, QString, int row = -1);
    Q_INVOKABLE void saveVariable(QString, QVariant);
    Q_INVOKABLE QVariant restoreVariable(QString);
    void saveVariablesToDB();
    void restoreVariablesFromDB();
    Q_INVOKABLE virtual void setEnabled(bool);
    Q_INVOKABLE virtual void setForm(QString = "");
    Q_INVOKABLE virtual void updateCurrentRow(int = 0);
    Q_INVOKABLE void loadDocument();        // Загружает документ перед тем, как его показать
    Q_INVOKABLE bool isModified();
    Q_INVOKABLE void calcItog();
    bool isSinglePrv();
    bool isQuanAccount();
    Q_INVOKABLE virtual bool saveChanges();
    Q_INVOKABLE bool lockDocument();
    Q_INVOKABLE void unlockDocument();

};

#endif // DOCUMENT_H
