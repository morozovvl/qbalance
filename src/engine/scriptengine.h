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

#include <QScriptValue>
#include <QScriptEngine>
#include "sqlqueryclass.h"
#include "sqlrecordclass.h"
#include "sqlfieldclass.h"

class Form;

struct EventFunction {
    QString     name;
    QString     comment;
};


class ScriptEngine : public QScriptEngine {
    Q_OBJECT
public:
    explicit ScriptEngine(QObject *parent = 0);
    ~ScriptEngine();
    bool open(QString fileName = "");
    bool evaluate();
    QString getErrorMessage() { return errorMessage; }
    bool getScriptResult() { return scriptResult; }
// События
    virtual QList<EventFunction>* getEventsList();
    QString getBlankScripts();
    void eventInitForm(Form*);
    void eventBeforeShowForm(Form*);
    void eventAfterHideForm(Form*);
    void eventCloseForm(Form*);
    void eventImport(Form*);
    void eventExport(Form*);
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
