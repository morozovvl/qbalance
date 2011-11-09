#ifndef SQLFIELDPROTOTYPE_H
#define SQLFIELDPROTOTYPE_H

#include <QObject>
#include <QScriptable>
#include <QScriptValue>
#include <QSqlField>
#include <QSqlError>
#include <QVariant>
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
