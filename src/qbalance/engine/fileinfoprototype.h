#ifndef FILEINFOPROTOTYPE_H
#define FILEINFOPROTOTYPE_H

#include <QtCore/QObject>
#include <QtCore/QFileInfo>
#include <QtScript/QScriptable>
#include <QtScript/QScriptValue>


class FileInfoPrototype : public QObject, public QScriptable
{
    Q_OBJECT

public:
    FileInfoPrototype(QObject *parent = nullptr);
    ~FileInfoPrototype();

public slots:
    QScriptValue valueOf() const;
    QScriptValue suffix() const;

private:
    QFileInfo *thisFileInfo() const;
};

#endif // FILEINFOPROTOTYPE_H
