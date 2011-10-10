#ifndef TOPERS_H
#define TOPERS_H

#include <QString>
#include "dictionary.h"

class Topers : public Dictionary {
public:
    Topers(QObject *parent = 0);
    QVariant getToperProperty(int, QString);
    QString getDocumentTitle(QString);
    void cmdOk();

private:
    QSqlQuery topersProperties;
    void addDocuments(int);
};

#endif // TOPERS_H
