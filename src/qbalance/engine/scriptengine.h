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

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QPushButton>
    #include <QtGui/QFileDialog>
    #include <QtGui/QLineEdit>
#else
    #include <QtWidgets/QPushButton>
    #include <QtWidgets/QFileDialog>
    #include <QtWidgets/QLineEdit>
#endif


#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>
#include <QtGui/QKeyEvent>
//#include <gsl/gsl_sf_bessel.h>


class Form;
class Essence;
class TApplication;
class Document;
class Documents;
class ReportContext;
class SqlQueryClass;
class SqlRecordClass;
class SqlFieldClass;


struct EventFunction {
    QString     comment;
    QString     body;
};


class ScriptEngine : public QScriptEngine {
    Q_OBJECT
public:
    ScriptEngine(Essence* parent = 0 /*nullptr*/);
    ~ScriptEngine();
    virtual bool open(QString fileName = "");
    virtual void close();
    virtual bool evaluate();
    virtual QScriptValue evaluate(QString);
    QString getErrorMessage();
    virtual void setErrorMessage(QString error = "");
    int getScriptResult();
    virtual void    setScriptError();
    virtual bool    getScriptError();
    void setIsDocumentScript(bool docScr);
    QString getScriptFileName();
    Essence* getParent();
    Document* getDocument();
//    virtual QScriptValue globalObject();
// События
    virtual QHash<QString, EventFunction>* getEventsList();
    virtual void    appendEvent(QString, EventFunction*);
    virtual QString getBlankScripts();
    virtual void eventAfterCalculate();
    virtual void eventParametersChanged();
    virtual bool eventBeforeAddString();
    virtual void eventAfterAddString();
    virtual bool eventAfterShowNextDicts();
    virtual bool eventBeforeDeleteDocument();
    virtual void eventAfterDeleteDocument();
    virtual bool eventBeforeDeleteString();
    virtual void eventAfterDeleteString();
    virtual void eventInitForm(Form*);
    virtual void eventBeforeShowForm(Form*);
    virtual void eventAfterShowForm(Form*);
    virtual bool eventBeforeHideForm(Form*);
    virtual void eventAfterHideForm(Form*);
    virtual void eventCloseForm(Form*);
    virtual void eventImport(Form*);
    virtual void eventExport(Form*);
    virtual void eventQuery();
    virtual void eventCalcTable();
    virtual void eventSetEnabled(bool);
    virtual void eventAfterRowChanged();
    virtual void eventBeforeRowChanged();
    virtual void eventPhotoLoaded();
    virtual void eventPreparePrintValues();
    virtual QString preparePictureUrl(Essence*);
    virtual QString prepareBarCodeData(Essence*);
    virtual QString getFilter(QString = "");
    virtual bool eventBarCodeReaded(QString);
    virtual void eventCardCodeReaded(QString);
    virtual bool eventKeyPressed(int, int);
    friend bool isNumeric(ScriptEngine engine, QString field);
    static QString loadScript(QString);
    static void removeScript(QString);
    void   showScriptError();

protected:
    QHash<QString, EventFunction> eventsList;          // Список доступных в скриптах событий с комментариями
    QString         script;
    Document*       document;
    Documents*      documents;
    virtual void    loadScriptObjects();

    QScriptValue      scriptCall(QString, const QScriptValue & thisObject = QScriptValue(), const QScriptValueList & args = QScriptValueList());

private:
    static QHash<QString, QString> scripts;
    int                 scriptResult;
    QString             errorMessage;
    bool                scriptError;
    QString             lastErrorMessage;
    QString             scriptFileName;
    SqlQueryClass*      sqlQueryClass;
    SqlRecordClass*     sqlRecordClass;
    SqlFieldClass*      sqlFieldClass;
    TApplication*       app;
    Essence*            parent;
    static bool         isSA;
    bool                tryEventLoopExit;


private slots:
    void        tryEventLoop();
};


#endif // SCRIPTENGINE_H
