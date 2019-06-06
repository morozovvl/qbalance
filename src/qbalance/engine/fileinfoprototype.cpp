#include <QtScript/QScriptEngine>
#include <QDebug>
#include "fileinfoprototype.h"

Q_DECLARE_METATYPE(QFileInfo*)

FileInfoPrototype::FileInfoPrototype(QObject *parent) : QObject(parent)
{
}

FileInfoPrototype::~FileInfoPrototype()
{
}

QFileInfo *FileInfoPrototype::thisFileInfo() const
{
    return qscriptvalue_cast<QFileInfo*>(thisObject().data());
}

QScriptValue FileInfoPrototype::valueOf() const
{
    return thisObject().data();
}


QScriptValue FileInfoPrototype::suffix() const
{
    qDebug() << thisFileInfo()->suffix();
    return thisFileInfo()->suffix();
}
