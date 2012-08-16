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

#include <QSqlTableModel>
#include <QString>
#include <QMap>
#include "essence.h"
#include "dictionaries.h"
#include "documents.h"
#include "../engine/documentscriptengine.h"
#include "../gui/formdocument.h"


class TApplication;
class DocumentTableModel;

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
    virtual ~Document();
    Q_INVOKABLE int getDocId() { return docId; }
    Q_INVOKABLE int getOperNumber() { return operNumber; }
    Documents* getParent() { return parent; }
    QMap<QString, Dictionary*>* getDictionaries() { return dicts; }
    Q_INVOKABLE Dictionary* getDictionary(QString dictName, int deep = 0, bool add = true) { return dictionaries->getDictionary(dictName, deep, add); }
    Q_INVOKABLE Saldo* getSaldo(QString acc, QString dictName, int deep = 0) { return dictionaries->getSaldo(acc, dictName, deep); }
    Q_INVOKABLE virtual bool add();
    Q_INVOKABLE virtual bool remove();
    Q_INVOKABLE virtual void show();
    virtual QString transformSelectStatement(QString string);
    void setDocId(int doc) { docId = doc; }
    virtual bool calculate(const QModelIndex &);
    virtual void setConstDictId(QString, QVariant);
    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();
    virtual void query(QString filter = "");
    virtual void setScriptEngine();
    int    addFromQuery(int);
    DocumentScriptEngine* getScriptEngine();
    bool getIsSingleString() { return isSingleString; }
    Q_INVOKABLE void setDate(QString date, Qt::DateFormat format = Qt::TextDate) { ((FormDocument*)getForm())->setDate(QDate::fromString(date, format)); }
    Q_INVOKABLE void setNumber(QString number) { ((FormDocument*)getForm())->setNumber(number); }
    Q_INVOKABLE void showParameterText(QString dictName) { ((FormDocument*)getForm())->showParameterText(dictName);}
    Q_INVOKABLE void appendDocString();
    Q_INVOKABLE void setPrvValue(QString name, QVariant value) { prvValues.insert(name, value); }
    Q_INVOKABLE void setValue(QString name, QVariant value, int row = -1);
    Q_INVOKABLE QVariant getSumValue(QString name);
    Q_INVOKABLE void calcItog();
    Q_INVOKABLE void saveVariable(QString, QVariant);
    Q_INVOKABLE QVariant restoreVariable(QString);
    void saveVariablesToDB();
    void restoreVariablesFromDB();

protected:
    virtual void setForm();
    virtual void preparePrintValues(ReportScriptEngine*);     // Готовит значения для печати
private:
    QMap<QString, Dictionary*>*     dicts;              // Объекты справочников
    QMap<QString, QVariant>         prvValues;          // Значения проводок для сохранения в БД из процедуры appendDocString
    QMap<QString, QVariant>         variables;          // Значения переменных, используемых в скриптах для восстановления или последующего сохранения в БД
    Dictionaries*                   dictionaries;       // Объекты справочников
    Documents*                      parent;
    int                             operNumber;
    int                             docId;
    int                             prv1;
    int                             freePrv;            // Номер "свободной" проводки
    bool                            isSingleString;     // В документе должна присутствовать только одна строка (для платежных поручений, например)
    QList<ToperType>                topersList;
    QString                         selectStatement;
    QHash<int, prvSaldo>            saldo;             // содержит остаток и сальдо по счетам, корреспондирующим в текущей строке документа
    virtual void setTableModel();
    bool showNextDict();
    void selectCurrentRow();
    void showItog();
};

#endif // DOCUMENT_H
