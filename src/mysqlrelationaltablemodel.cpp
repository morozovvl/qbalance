#include <QModelIndex>
#include <QVariant>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlResult>
#include <QStringList>
#include <QSqlRelation>
#include <QSqlDriver>
#include <QDebug>
#include <QSqlError>
#include <QMap>
#include <QUuid>
#include <QLocale>
#include "mysqlrelationaltablemodel.h"
#include "table.h"
#include "mysqlquery.h"

MySqlRelationalTableModel::MySqlRelationalTableModel() : QSqlRelationalTableModel() {
    parent = NULL;
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    relIsEmpty = true;                           // по умолчанию нет реляционных отношений
    sortClause = "";
    isPrepared = false;
    blockUpdate = false;
    preparedStatementName = "";
    preparedStatement = "";
}

bool MySqlRelationalTableModel::insertColumns(int column, int count, const QModelIndex & parent) {
    if (QSqlQueryModel::insertColumns(column, count, parent)) {
        for (int i = 0; i < count; i++)
            insertedColumns.append(column + i);
        return true;
    }
    return false;
}

int MySqlRelationalTableModel::fieldIndex(const QString &fieldName) const {
    int result;
    result = QSqlTableModel::fieldIndex(fieldName);
    if (result >= 0)
        return result;
    for (int i = 0; i < insertedColumns.size(); i++) {
        QString fldName = relation(insertedColumns[i]).tableName() + "." + relation(insertedColumns[i]).displayColumn();
        if (fieldName == fldName)
            return insertedColumns[i];
    }
    if (fieldsList.size() > 0 && fieldsList.contains(fieldName))
        return fieldsList.indexOf(fieldName);
    return -1;
}

bool MySqlRelationalTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
//    Q_UNUSED(role)
    bool lResult = false;
    if (indexInQuery(index).isValid() && !insertedColumns.contains(index.column()))
    {  // Если столбец не числится среди добавленных столбцов, для добавленных столбцов ничего не будем делать
        if (!blockUpdate && value != data(index))
        {   // Если данные разрешено модифицировать
            // и новые данные не равны старым
            QSqlRecord rec = record(index.row());
//            if (rec.indexOf("код") != index.column())
//            {   // Если мы не пытаемся поменять значение ключевого столбца
                rec.setValue(index.column(), value);
                rec.setGenerated(index.column(), true);
                for (int i = insertedColumns.count() - 1; i >= 0; i--)
                {   // Для корректной генерации команды сохранения
                    // уберем добавленные столбцы из записи
                    rec.remove(insertedColumns[i]);
                }
//                lResult = updateRowInTable(index.row(), rec);
                QSqlRelationalTableModel::setData(index, value, role);
//            }
        }
        else
        {
            lResult = true;
        }
    }
    return lResult;
}


bool MySqlRelationalTableModel::updateRowInTable(int row, const QSqlRecord &values) {
    if (!blockUpdate)
        return QSqlRelationalTableModel::updateRowInTable(row, values);
    return true;
}


QStringList MySqlRelationalTableModel::getFieldsList() {
    if (fieldsList.count() == 0) {
        for (int i = 0; i < record().count(); i++)
            fieldsList << record().fieldName(i);
    }
    return fieldsList;
}

/*
void MySqlRelationalTableModel::setFieldsList(QStringList list) {
    if (insertedColumns.size() == 0)                // Если реляции уже заданы, то нельзя переназначать список полей во избежание неправильной генерации SQL команды
        fieldsList = list;
}
*/

void MySqlRelationalTableModel::setRelation(int column, const QSqlRelation &relation) {
    relIsEmpty = false;
    QSqlRelationalTableModel::setRelation(column, relation);
}

void MySqlRelationalTableModel::setRelation(int column, int keyColumn, const QSqlRelation &relation) {
    relIsEmpty = false;
// устанавливает реляционную связь relation для колонки column на основании ключа в колонке keyColumn
    if ((column >= 0 && column < columnCount()) &&          // Если колонка с таким номером присутствует
         (relationModel(column) == 0) &&                    // Если для колонки column еще не установлена реляционная связь
         (relationModel(keyColumn) != 0)) {                  // а для колонки keyColumn реляционная связь наоборот установлена
        keyColumns.insert(column, keyColumn);
        QSqlRelationalTableModel::setRelation(column, relation);
    }
}

void MySqlRelationalTableModel::setSort(int column, Qt::SortOrder order) {
    sortColumn = column;
    sortOrder = order;
}

QString MySqlRelationalTableModel::orderByClause() const {
    if (sortClause.size() > 0)
        return QString("ORDER BY %1").arg(sortClause);
    QString s;
    QSqlField f = record().field(sortColumn);
    if (!f.isValid())
        return s;
    QString table;
    QString field;
    if (relationModel(sortColumn) == 0) {
        table = database().driver()->escapeIdentifier(tableName(), QSqlDriver::TableName);
        field = database().driver()->escapeIdentifier(f.name(), QSqlDriver::FieldName);
    }
    else {
        QSqlRelation rel = relation(sortColumn);
        if (rel.isValid()) {
            table = database().driver()->escapeIdentifier(rel.tableName(), QSqlDriver::TableName);
            field = database().driver()->escapeIdentifier(rel.displayColumn(), QSqlDriver::FieldName);
        }
    }
    if ((table.size() > 0) && (field.size() > 0)) {
        s.append(QLatin1String("ORDER BY ")).append(table).append(QLatin1Char('.')).append(field);
        s += sortOrder == Qt::AscendingOrder ? QLatin1String(" ASC") : QLatin1String(" DESC");
    }
    return s;
}

void MySqlRelationalTableModel::setSelectClause(QString string) {
    if (string.size() == 0)
        selectClause = getSelectClause();
    else
        selectClause = string;
}

void MySqlRelationalTableModel::setSelectStatement(QString string) {
    selectCommand = string;
}

QString MySqlRelationalTableModel::selectStatement() const {
    QString query;
    if (selectCommand.size() > 0)
        query = selectCommand;
    else {
        if (selectClause.size() > 0)            // Если уже имеется готовый текст запроса
            query = selectClause;
        else                                    // Иначе создадим его заново
            query = getSelectClause();
        if (query.size() > 0) {
            if (!filter().isEmpty())
                query.append(QLatin1String(" WHERE ")).append(filter());
            if (!orderByClause().isEmpty())
                query.append(QLatin1Char(' ')).append(orderByClause());
        }
    }
    if (parent != NULL)
        query = parent->transformSelectStatement(query);

    return query;
}

/*  Не понял, для чего. Вроде нигде не вызывается
QString MySqlRelationalTableModel::getPreparedSelectStatement() const {
    if (preparedStatementName == "") {
        preparedStatementName = tableName().append('-').append(QUuid().createUuid().toString().remove('{').remove('}'));
        preparedStatement = QString("EXECUTE %1()").arg(preparedStatementName);
    }
    if (preparedStatement.length() > 0)
        return preparedStatement;
    return QString();
}
*/

QString MySqlRelationalTableModel::getSelectClause() const {
    QString query;
    if (!tableName().isEmpty()) {
        QString selectList;
        QString fromList;
        QStringList aliases;

        fromList = database().driver()->escapeIdentifier(tableName(), QSqlDriver::TableName);
        if (tableAlias.size() > 0) {
            fromList.append(" ").append(database().driver()->escapeIdentifier(tableAlias, QSqlDriver::TableName));
            aliases << tableAlias;
        }
        else
            aliases << tableName();
        QSqlRecord rec = record();
        for (int i = 0; i < rec.count(); ++i)               // составим список полей для секции SELECT
            if (!insertedColumns.contains(i)) {           // в исходный список полей включим только те поля, которые не были добавлены при создании реляций
                if ((fieldsList.size() == 0) || fieldsList.contains(rec.fieldName(i))) {
                    if (tableAlias.size() > 0) {
                        selectList.append(escapedRelationField(tableAlias, rec.fieldName(i)));
                        selectList.append(QString::fromLatin1(" AS %1__%2").arg(tableAlias).arg(rec.fieldName(i)));
                        selectList.append(QLatin1Char(','));
                    }
                    else
                        selectList.append(escapedRelationField(tableName(), rec.fieldName(i))).append(QLatin1Char(','));
                }
            }
        if (insertedColumns.size() > 0) {
            for (QMap<int, int>::const_iterator it = keyColumns.constBegin(); it != keyColumns.constEnd(); it++) {
                QSqlRelation relation = QSqlRelationalTableModel::relation(it.key());
                QString alias = tablesAliases.contains(it.key()) ? tablesAliases.value(it.key()) : relation.tableName();
                selectList.append(escapedRelationField(alias, relation.displayColumn()));
                selectList.append(QString::fromLatin1(" AS %1__%2").arg(alias).arg(relation.displayColumn()));
                selectList.append(QLatin1Char(','));
                if (!aliases.contains(alias)) {
                    fromList.append(" LEFT OUTER JOIN ").append(database().driver()->escapeIdentifier(relation.tableName(), QSqlDriver::TableName));
                    if (tablesAliases.value(it.key()).size() > 0 && QString(relation.tableName()).compare(tablesAliases.value(it.key())) != 0)          // если имя таблицы и ее алиас не совпадают
                        fromList.append(" ").append(database().driver()->escapeIdentifier(tablesAliases.value(it.key()), QSqlDriver::TableName));
                    fromList.append(" ON ").append(escapedRelationField((tableAlias.size() == 0 ? tableName() : tableAlias), rec.fieldName(it.value())));
                    fromList.append(QLatin1Char('='));
                    fromList.append(escapedRelationField(alias, relation.indexColumn()));
                    aliases << alias;
                }
            }
        }
        selectList.chop(1);
        query.append(QLatin1String("SELECT DISTINCT ")).append(selectList);;
        query.append(QLatin1String(" FROM ")).append(fromList);
    }
    return query;
}

QString MySqlRelationalTableModel::escapedRelationField(const QString &tableName, const QString &fieldName) const {
    QString esc;
    esc.reserve(tableName.size() + fieldName.size() + 1);
    esc.append(tableName).append(QLatin1Char('.')).append(fieldName);
    return database().driver()->escapeIdentifier(esc, QSqlDriver::FieldName);
}

MySqlQuery* MySqlRelationalTableModel::query() {
    QSqlQuery query(QSqlRelationalTableModel::query());
    return new MySqlQuery(query);
}
