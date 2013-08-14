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
#include <QtCore/QMap>
#include "essence.h"
#include "dictionaries.h"
#include "documents.h"
#include "../engine/documentscriptengine.h"
#include "../gui/formdocument.h"


class TApplication;

struct prvSaldo {
    double  dbQuan;
    double  dbSaldo;
    double  crQuan;
    double  crSaldo;
};

class Document : public Essence {
    Q_OBJECT
public:
    Document(int, Documents*);
    ~Document();
    Q_INVOKABLE int getDocId() { return docId; }
    Q_INVOKABLE int getOperNumber() { return operNumber; }
    Documents* getParent() { return parent; }
    QMap<QString, Dictionary*>* getDictionaries() { return dictionaries->getDictionaries(); }
    Q_INVOKABLE Dictionary* getDictionary(QString dictName, int deep = 0, bool add = true) { return dictionaries->getDictionary(dictName, deep, add); }
    Q_INVOKABLE Saldo* getSaldo(QString acc) { return dictionaries->getSaldo(acc); }
    Q_INVOKABLE virtual bool add();
    Q_INVOKABLE virtual bool remove();
    Q_INVOKABLE virtual void show();
    virtual void cmdOk();                       // Обработка нажатий кнопок "Ok"
    virtual void cmdCancel();                   // и "Cancel"
    virtual QString transformSelectStatement(QString string);
    void setDocId(int doc) { docId = doc; }
    virtual bool calculate(const QModelIndex &);
    virtual void setConstDictId(QString, QVariant);
    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();
    virtual void setScriptEngine();
    int    addFromQuery(int);
    DocumentScriptEngine* getScriptEngine();
    bool getIsSingleString() { return isSingleString; }
    Q_INVOKABLE void setDate(QString date, Qt::DateFormat format = Qt::TextDate) { getForm()->setDate(QDate::fromString(date, format)); }
    Q_INVOKABLE void setNumber(QString number) { getForm()->setNumber(number); }
    Q_INVOKABLE void showParameterText(QString dictName) { getForm()->showParameterText(dictName);}
    int appendDocString();
    bool prepareValue(QString, Dictionary*);
    Q_INVOKABLE virtual void setValue(QString name, QVariant value, int row = -1);
    Q_INVOKABLE virtual QVariant getValue(QString, int row = -1);
    Q_INVOKABLE QVariant getSumValue(QString name);
    Q_INVOKABLE void saveVariable(QString, QVariant);
    Q_INVOKABLE QVariant restoreVariable(QString);
    Q_INVOKABLE void saveChanges();
    void saveVariablesToDB();
    void restoreVariablesFromDB();
    virtual void        saveOldValues();                // Сохраняет значения полей текущей строки перед вычислениями
    virtual void        restoreOldValues();
    Q_INVOKABLE virtual void setEnabled(bool);
    virtual FormDocument* getForm() { return (FormDocument*)Essence::getForm(); }
    Q_INVOKABLE virtual void setForm(QString = "");



protected:
    virtual void        preparePrintValues(ReportScriptEngine*);     // Готовит значения для печати
    virtual void        prepareSelectCurrentRowCommand();
    virtual void        updateCurrentRow(int = 0);
    virtual bool        setTableModel(int = 0);

private:
    QMap<QString, QVariant>         prvValues;          // Значения проводок для сохранения в БД из процедуры appendDocString
    QMap<QString, QVariant>         variables;          // Значения переменных, используемых в скриптах для восстановления или последующего сохранения в БД
    Dictionaries*                   dictionaries;       // Объекты справочников
    Documents*                      parent;
    int                             operNumber;
    int                             docId;
    int                             prv1;
    int                             freePrv;            // Номер "свободной" проводки
    bool                            isSingleString;     // В документе должна присутствовать только одна строка (для платежных поручений, например)
    QList<QString>                  attrFields;         // Имена полей атрибутов документа, которые могут добавляться при добавлении новой строки
    QString                         selectStatement;
    QMap<QString, QVariant>         oldValues0;         // Старые значения для первой строки документа - там хранятся значения "свободной" проводки
    QList<ToperType>*               topersList;
    bool                            localDictsOpened;

    bool showNextDict();
    void showItog();
    void calcItog();
    int findFreePrv();              // Ищет строку, в которой отображена "свободная" проводка, т.к. она может быть и не в первой строке
    bool    compareSumValues();     // Сравнивает новые значения полей СУММА проводок со старыми. Если значения различаются, то дается добро на сохранение данных проводки на сервере
    void    openLocalDictionaries();
};

#endif // DOCUMENT_H