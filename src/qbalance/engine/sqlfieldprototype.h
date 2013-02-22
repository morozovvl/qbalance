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

#ifndef SQLFIELDPROTOTYPE_H
#define SQLFIELDPROTOTYPE_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptValue>
#include <QtSql/QSqlField>
#include <QtSql/QSqlError>
#include <QtCore/QVariant>
#include "sqlfieldclass.h"


class SqlFieldPrototype : public QObject, public QScriptable
{
    Q_OBJECT
public:
    SqlFieldPrototype(QObject*);
    ~SqlFieldPrototype();
public slots:
    void            clear()                         { thisSqlField()->clear(); }
    QVariant        defaultValue() const            { return thisSqlField()->defaultValue(); }
    bool            isAutoValue() const             { return thisSqlField()->isAutoValue(); }
    bool            isGenerated() const             { return thisSqlField()->isGenerated(); }
    bool            isNull() const                  { return thisSqlField()->isNull(); }
    bool            isReadOnly() const              { return thisSqlField()->isReadOnly(); }
    bool            isValid() const                 { return thisSqlField()->isValid(); }
    int             length() const                  { return thisSqlField()->length(); }
    QString         name() const                    { return thisSqlField()->name(); }
    int             precision() const               { return thisSqlField()->precision(); }
    QSqlField::RequiredStatus  requiredStatus() const          { return thisSqlField()->requiredStatus(); }
    void            setAutoValue(bool autoVal)      { thisSqlField()->setAutoValue(autoVal); }
    void            setDefaultValue(const QVariant &value)      { thisSqlField()->setDefaultValue(value); }
    void            setGenerated(bool gen)          { thisSqlField()->setGenerated(gen); }
    void            setLength(int fieldLength)      { thisSqlField()->setLength(fieldLength); }
    void            setName(const QString &name)    { thisSqlField()->setName(name); }
    void            setPrecision(int precision)     { thisSqlField()->setPrecision(precision); }
    void            setReadOnly(bool readOnly)      { thisSqlField()->setReadOnly(readOnly); }
    void            setRequired(bool required)      { thisSqlField()->setRequired(required); }
    void            setRequiredStatus(QSqlField::RequiredStatus required)  { thisSqlField()->setRequiredStatus(required); }
    void            setType(QVariant::Type type)    { thisSqlField()->setType(type); }
    void            setValue(const QVariant &value) { thisSqlField()->setValue(value); }
    QVariant::Type  type() const                    { return thisSqlField()->type(); }
    QVariant        value() const                   { return thisSqlField()->value(); }
private:
    QSqlField*          thisSqlField() const;
};

#endif // SQLFIELDPROTOTYPE_H
