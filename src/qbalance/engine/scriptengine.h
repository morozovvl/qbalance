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

#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>
#include <QtGui/QKeyEvent>
#include "sqlqueryclass.h"
#include "sqlrecordclass.h"
#include "sqlfieldclass.h"


class Form;
class Essence;
class TApplication;
class Document;
class Documents;
class ReportContext;


struct EventFunction {
    QString     comment;
    QString     body;
};


class ScriptEngine : public QScriptEngine {
    Q_OBJECT
public:
    ScriptEngine(Essence* parent = 0);
    ~ScriptEngine();
    bool open(QString fileName = "");
    void close();
    bool evaluate();
//    QScriptValue evaluate(const QString &, const QString & = QString(), int = 1);
    QScriptValue evaluate(const QString &, const QString &, int);
    QScriptValue evaluate(const QScriptProgram &);
    QString getErrorMessage() { return errorMessage; }
    void setErrorMessage(QString error = "") { globalObject().setProperty("errorMessage", error); }
    int getScriptResult() { return scriptResult; }
    void setIsDocumentScript(bool docScr) { globalObject().setProperty("isDocumentScript", docScr); }
    QString getScriptFileName() { return scriptFileName; }
    Essence* getParent() { return parent; }
    Document* getDocument() { return document; }
// События
    virtual QHash<QString, EventFunction>* getEventsList();
    void    appendEvent(QString, EventFunction*);
    QString getBlankScripts();
    void eventAfterCalculate();
    void eventParametersChanged();
    bool eventBeforeAddString();
    void eventAfterAddString();
    bool eventAfterShowNextDicts();
    void eventBeforeDeleteString();
    void eventAfterDeleteString();
    void eventInitForm(Form*);
    void eventBeforeShowForm(Form*);
    void eventAfterShowForm(Form*);
    void eventBeforeHideForm(Form*);
    void eventAfterHideForm(Form*);
    void eventCloseForm(Form*);
    void eventImport(Form*);
    void eventExport(Form*);
    void eventCalcTable();
    void eventSetEnabled(bool);
    void eventAfterRowChanged();
    void eventBeforeRowChanged();
    void eventPhotoLoaded();
    void eventPreparePrintValues();
    QString preparePictureUrl(Essence*);
    QString getFilter(QString = "");
    void eventBarCodeReaded(QString);
    void eventCardCodeReaded(QString);
    bool eventKeyPressed(int, int);
    friend bool isNumeric(ScriptEngine engine, QString field);
    static QString loadScript(QString);
    static void removeScript(QString);
    void   showScriptError(QString);

protected:
    QScriptValue      scriptCall(QString, const QScriptValue & thisObject = QScriptValue(), const QScriptValueList & args = QScriptValueList());

protected:
    QHash<QString, EventFunction> eventsList;          // Список доступных в скриптах событий с комментариями
    QString         script;
    Document*       document;
    Documents*      documents;
    virtual void    loadScriptObjects();
private:
    static QHash<QString, QString> scripts;
    int                 scriptResult;
    QString             errorMessage;
    QString             scriptFileName;
    SqlQueryClass*      sqlQueryClass;
    SqlRecordClass*     sqlRecordClass;
    SqlFieldClass*      sqlFieldClass;
    TApplication*       app;
    Essence*            parent;
    static bool         isSA;
};


#endif // SCRIPTENGINE_H
