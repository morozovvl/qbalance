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


class SqlFieldPrototype : public QObject, public QScriptable
{
    Q_OBJECT
public:
    SqlFieldPrototype(QObject*);
    ~SqlFieldPrototype();
public slots:
    void            clear();
    QVariant        defaultValue() const;
    bool            isAutoValue() const;
    bool            isGenerated() const ;
    bool            isNull() const;
    bool            isReadOnly() const;
    bool            isValid() const;
    int             length() const;
    QString         name() const;
    int             precision() const;
    QSqlField::RequiredStatus  requiredStatus() const;
    void            setAutoValue(bool autoVal);
    void            setDefaultValue(const QVariant &value);
    void            setGenerated(bool gen);
    void            setLength(int fieldLength);
    void            setName(const QString &name);
    void            setPrecision(int precision);
    void            setReadOnly(bool readOnly);
    void            setRequired(bool required);
    void            setRequiredStatus(QSqlField::RequiredStatus required);
    void            setType(QVariant::Type type);
    void            setValue(const QVariant &value);
    QVariant::Type  type() const;
    QVariant        value() const;
private:
    QSqlField*          thisSqlField() const;
};

#endif // SQLFIELDPROTOTYPE_H
