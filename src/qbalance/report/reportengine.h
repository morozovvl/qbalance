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

#ifndef REPORTENGINE_H
#define REPORTENGINE_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptContext>
#include "../kernel/essence.h"

class Essence;

class ReportEngine : public QObject {
    Q_OBJECT
public:
    ReportEngine(ReportScriptEngine* = 0);
    ~ReportEngine();
    virtual bool open() { return true; }
    virtual void close() { return; }
    virtual bool open(QMap<QString, QVariant>* context, QString name, QString ext);

protected:
    QMap<QString, QVariant>*            reportContext;
    QString                             reportName;
    QString                             reportExt;
    ReportScriptEngine*                 scriptEngine;
};

#endif // REPORTENGINE_H
