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

struct EventFunction {
    QString     name;
    QString     comment;
};


class ScriptEngine : public QScriptEngine {
    Q_OBJECT
public:
    ScriptEngine(QObject *parent = 0);
    ~ScriptEngine();
    bool open(QString fileName = "");
    bool evaluate();
    QScriptValue evaluate (const QString &, const QString & = QString(), int = 1);
    QString getErrorMessage() { return errorMessage; }
    bool getScriptResult() { return scriptResult; }
// События
    virtual QList<EventFunction>* getEventsList();
    QString getBlankScripts();
    void eventAfterCalculate();
    void eventParametersChanged();
    void eventBeforeAddString();
    void eventAfterAddString();
    void eventInitForm(Form*);
    void eventBeforeShowForm(Form*);
    void eventAfterHideForm(Form*);
    void eventCloseForm(Form*);
    void eventImport(Form*);
    void eventExport(Form*);
    virtual QString preparePictureUrl(Essence*);
    friend bool isNumeric(ScriptEngine engine, QString field);
protected:
    QList<EventFunction> eventsList;          // Список доступных в скриптах событий с комментариями
    virtual void loadScriptObjects();
private:
    bool                scriptResult;
    QString             script;
    QString             errorMessage;
    QString             scriptFileName;
    SqlQueryClass*      sqlQueryClass;
    SqlRecordClass*     sqlRecordClass;
    SqlFieldClass*      sqlFieldClass;
};


#endif // SCRIPTENGINE_H
