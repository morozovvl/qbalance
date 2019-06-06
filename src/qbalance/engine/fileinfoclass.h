#ifndef FILEINFOCLASS_H
#define FILEINFOCLASS_H

#include <QtCore/QObject>
#include <QtCore/QFileInfo>
#include <QtScript/QScriptClass>
#include <QtScript/QScriptString>

QT_BEGIN_NAMESPACE
class QScriptContext;
QT_END_NAMESPACE


class FileInfoClass : public QObject, public QScriptClass
{
    Q_OBJECT

public:
    FileInfoClass(QScriptEngine *engine);
    ~FileInfoClass();

    QScriptValue constructor();

    QScriptValue newInstance();
    QScriptValue newInstance(const QFileInfo &ba);
/*
    QueryFlags queryProperty(const QScriptValue &object, const QScriptString &name, QueryFlags flags, uint *id);

    QScriptValue property(const QScriptValue &object, const QScriptString &name, uint id);

    void setProperty(QScriptValue &object, const QScriptString &name, uint id, const QScriptValue &value);

    QScriptValue::PropertyFlags propertyFlags(const QScriptValue &object, const QScriptString &name, uint id);
*/
    QString name() const;

    QScriptValue prototype() const;

private:
    static QScriptValue construct(QScriptContext *ctx, QScriptEngine *eng);

    static QScriptValue toScriptValue(QScriptEngine *eng, const QFileInfo &ba);
    static void fromScriptValue(const QScriptValue &obj, QFileInfo &ba);

    void resize(QFileInfo &ba, int newSize);

//    QScriptString length;
    QScriptValue proto;
    QScriptValue ctor;

};

#endif // FILEINFOCLASS_H
