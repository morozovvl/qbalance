#ifndef DOCUMENTTABLEMODEL_H
#define DOCUMENTTABLEMODEL_H

#include <QObject>
#include <QModelIndex>
#include <QVariant>
#include <QHash>
#include "mysqlrelationaltablemodel.h"

class App;
extern App* app;

class DocumentTableModel : public MySqlRelationalTableModel {
    Q_OBJECT
public:
    DocumentTableModel();
    void setUpdateInfo(int, int, QString);
    virtual bool submit(const QModelIndex&);
private:
    // Структуры updateKeys и updateFields хранят записи, необходимые для генерации команды сохранения данных
    QList<int> updateKeys;                   // Список ключевых полей
    QHash<int, int> updateKeyFields;   // Хранит номер ключевого столбца
    QHash<int, QString> updateFields;   // Хранит имя поля в БД для текущего столбца
};

#endif // DOCUMENTTABLEMODEL_H
