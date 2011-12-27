#ifndef SQLRECORD_H
#define SQLRECORD_H

#include <QObject>
#include <QScriptable>
#include <QVariant>
#include <QSqlRecord>


class MySqlRecord : public QObject, protected QScriptable
{
    Q_OBJECT
public:
    explicit MySqlRecord(QObject* parent = 0);
    ~MySqlRecord();
    void setRecord(QSqlRecord rec) { *record = rec; }

public slots:
    QVariant value(int index) const { return record->value(index); }
    QVariant value(const QString &name) const { return record->value(name); }
    QString myString() { return "MySqlRecord"; }

private:
    QSqlRecord* record;
};

#endif // SQLRECORD_H
