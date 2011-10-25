#ifndef REPORTCONTEXT_H
#define REPORTCONTEXT_H

#include <QObject>
#include <QMap>
#include <QVariant>

class ReportContext : public QObject
{
    Q_OBJECT
public:
    explicit ReportContext(QMap<QString, QVariant>*, QObject *parent = 0);
    Q_INVOKABLE int count() { return data->count(); }
    Q_INVOKABLE QVariant getValue(QString);
    Q_INVOKABLE void setValue(QString, QVariant);
//    Q_INVOKABLE void sortTable(QString);    // сортировка контекста печати в разделе таблица по заданному полю
private:
    QMap<QString, QVariant>*    data;
};

#endif // REPORTCONTEXT_H
