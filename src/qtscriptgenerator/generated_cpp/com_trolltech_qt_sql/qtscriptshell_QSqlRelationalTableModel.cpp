#include "qtscriptshell_QSqlRelationalTableModel.h"

#include <QtScript/QScriptEngine>
#include <QSize>
#include <QStringList>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qdatastream.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qsize.h>
#include <qsqldatabase.h>
#include <qsqlerror.h>
#include <qsqlindex.h>
#include <qsqlquery.h>
#include <qsqlrecord.h>
#include <qsqlrelationaltablemodel.h>
#include <qsqltablemodel.h>
#include <qstringlist.h>
#include <qvector.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QMimeData*)
Q_DECLARE_METATYPE(Qt::DropAction)
Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::ItemFlag>)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(QSqlRecord)
#if QT_VERSION < 0x050000
template <> \
struct QMetaTypeId< QMap<int,QVariant> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QMap<int,QVariant> >("QMap<int,QVariant>"); \
        return metatype_id; \
    } \
};
#else // QT_VERSION < 0x050000
template <> \
struct QMetaTypeId< QMap<int,QVariant> >
{
    enum { Defined = 1 };
    static int qt_metatype_id()
    {
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);
        if (const int id = metatype_id.loadAcquire())
            return id;
        const int newId = qRegisterMetaType< QMap<int,QVariant> >("QMap<int,QVariant>", reinterpret_cast< QMap<int,QVariant> *>(quintptr(-1)));
        metatype_id.storeRelease(newId);
        return newId;
    }
};
#endif
Q_DECLARE_METATYPE(QFlags<Qt::MatchFlag>)
Q_DECLARE_METATYPE(QList<QModelIndex>)
Q_DECLARE_METATYPE(QSqlTableModel*)
#if QT_VERSION < 0x050000
template <> \
struct QMetaTypeId< QHash<int,QByteArray> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QHash<int,QByteArray> >("QHash<int,QByteArray>"); \
        return metatype_id; \
    } \
};
#else // QT_VERSION < 0x050000
template <> \
struct QMetaTypeId< QHash<int,QByteArray> >
{
    enum { Defined = 1 };
    static int qt_metatype_id()
    {
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);
        if (const int id = metatype_id.loadAcquire())
            return id;
        const int newId = qRegisterMetaType< QHash<int,QByteArray> >("QHash<int,QByteArray>", reinterpret_cast< QHash<int,QByteArray> *>(quintptr(-1)));
        metatype_id.storeRelease(newId);
        return newId;
    }
};
#endif
Q_DECLARE_METATYPE(QSqlTableModel::EditStrategy)
Q_DECLARE_METATYPE(QSqlRelation)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QFlags<Qt::DropAction>)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QSqlRelationalTableModel::QtScriptShell_QSqlRelationalTableModel(QObject*  parent, QSqlDatabase  db)
    : QSqlRelationalTableModel(parent, db) {}

QtScriptShell_QSqlRelationalTableModel::~QtScriptShell_QSqlRelationalTableModel() {}

QModelIndex  QtScriptShell_QSqlRelationalTableModel::buddy(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("buddy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("buddy") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::buddy(index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QModelIndex _q_retval = qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::canDropMimeData(const QMimeData*  data, Qt::DropAction  action, int  row, int  column, const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("canDropMimeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canDropMimeData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::canDropMimeData(data, action, row, column, parent);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QMimeData *>(data))
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, parent)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::canFetchMore(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("canFetchMore");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canFetchMore") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::canFetchMore(parent);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSqlRelationalTableModel::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlRelationalTableModel::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSqlRelationalTableModel::clear()
{
    QScriptValue _q_function = __qtscript_self.property("clear");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("clear") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlRelationalTableModel::clear();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QSqlRelationalTableModel::columnCount(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("columnCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("columnCount") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::columnCount(parent);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSqlRelationalTableModel::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlRelationalTableModel::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

QVariant  QtScriptShell_QSqlRelationalTableModel::data(const QModelIndex&  item, int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::data(item, role);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVariant _q_retval = qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, item)
            << qScriptValueFromValue(_q_engine, role)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::deleteRowFromTable(int  row)
{
    QScriptValue _q_function = __qtscript_self.property("deleteRowFromTable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("deleteRowFromTable") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::deleteRowFromTable(row);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::dropMimeData(const QMimeData*  data, Qt::DropAction  action, int  row, int  column, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("dropMimeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dropMimeData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::dropMimeData(data, action, row, column, parent);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QMimeData *>(data))
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, parent)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::event(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::eventFilter(arg__1, arg__2);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSqlRelationalTableModel::fetchMore(const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("fetchMore");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchMore") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlRelationalTableModel::fetchMore(parent);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent));
        _q_function.setData(QScriptValue(false));
    }
}

Qt::ItemFlags  QtScriptShell_QSqlRelationalTableModel::flags(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("flags");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("flags") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::flags(index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        Qt::ItemFlags _q_retval = qscriptvalue_cast<Qt::ItemFlags >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QVariant  QtScriptShell_QSqlRelationalTableModel::headerData(int  section, Qt::Orientation  orientation, int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("headerData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("headerData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::headerData(section, orientation, role);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVariant _q_retval = qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, section)
            << qScriptValueFromValue(_q_engine, orientation)
            << qScriptValueFromValue(_q_engine, role)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QModelIndex  QtScriptShell_QSqlRelationalTableModel::index(int  row, int  column, const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("index");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("index") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::index(row, column, parent);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QModelIndex _q_retval = qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, parent)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QModelIndex  QtScriptShell_QSqlRelationalTableModel::indexInQuery(const QModelIndex&  item) const
{
    QScriptValue _q_function = __qtscript_self.property("indexInQuery");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexInQuery") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::indexInQuery(item);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QModelIndex _q_retval = qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, item)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::insertColumns(int  column, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("insertColumns");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertColumns") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::insertColumns(column, count, parent);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::insertRowIntoTable(const QSqlRecord&  values)
{
    QScriptValue _q_function = __qtscript_self.property("insertRowIntoTable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertRowIntoTable") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::insertRowIntoTable(values);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, values)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::insertRows(int  row, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("insertRows");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertRows") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::insertRows(row, count, parent);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QMap<int , QVariant >  QtScriptShell_QSqlRelationalTableModel::itemData(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("itemData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::itemData(index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QMap<int , QVariant > _q_retval = qscriptvalue_cast<QMap<int , QVariant > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QList<QModelIndex >  QtScriptShell_QSqlRelationalTableModel::match(const QModelIndex&  start, int  role, const QVariant&  value, int  hits, Qt::MatchFlags  flags) const
{
    QScriptValue _q_function = __qtscript_self.property("match");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("match") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::match(start, role, value, hits, flags);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QList<QModelIndex > _q_retval = qscriptvalue_cast<QList<QModelIndex > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, start)
            << qScriptValueFromValue(_q_engine, role)
            << qScriptValueFromValue(_q_engine, value)
            << qScriptValueFromValue(_q_engine, hits)
            << qScriptValueFromValue(_q_engine, flags)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QMimeData*  QtScriptShell_QSqlRelationalTableModel::mimeData(const QList<QModelIndex >&  indexes) const
{
    QScriptValue _q_function = __qtscript_self.property("mimeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mimeData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::mimeData(indexes);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QMimeData* _q_retval = qscriptvalue_cast<QMimeData* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, indexes)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QStringList  QtScriptShell_QSqlRelationalTableModel::mimeTypes() const
{
    QScriptValue _q_function = __qtscript_self.property("mimeTypes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mimeTypes") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::mimeTypes();
    } else {
        _q_function.setData(QScriptValue(true));
        QStringList _q_retval = qscriptvalue_cast<QStringList >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::moveColumns(const QModelIndex&  sourceParent, int  sourceColumn, int  count, const QModelIndex&  destinationParent, int  destinationChild)
{
    QScriptValue _q_function = __qtscript_self.property("moveColumns");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("moveColumns") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::moveColumns(sourceParent, sourceColumn, count, destinationParent, destinationChild);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, sourceParent)
            << qScriptValueFromValue(_q_engine, sourceColumn)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, destinationParent)
            << qScriptValueFromValue(_q_engine, destinationChild)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::moveRows(const QModelIndex&  sourceParent, int  sourceRow, int  count, const QModelIndex&  destinationParent, int  destinationChild)
{
    QScriptValue _q_function = __qtscript_self.property("moveRows");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("moveRows") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::moveRows(sourceParent, sourceRow, count, destinationParent, destinationChild);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, sourceParent)
            << qScriptValueFromValue(_q_engine, sourceRow)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, destinationParent)
            << qScriptValueFromValue(_q_engine, destinationChild)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QString  QtScriptShell_QSqlRelationalTableModel::orderByClause() const
{
    QScriptValue _q_function = __qtscript_self.property("orderByClause");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("orderByClause") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::orderByClause();
    } else {
        _q_function.setData(QScriptValue(true));
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSqlRelationalTableModel::queryChange()
{
    QScriptValue _q_function = __qtscript_self.property("queryChange");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("queryChange") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlRelationalTableModel::queryChange();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

QSqlTableModel*  QtScriptShell_QSqlRelationalTableModel::relationModel(int  column) const
{
    QScriptValue _q_function = __qtscript_self.property("relationModel");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("relationModel") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::relationModel(column);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QSqlTableModel* _q_retval = qscriptvalue_cast<QSqlTableModel* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::removeColumns(int  column, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("removeColumns");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("removeColumns") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::removeColumns(column, count, parent);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::removeRows(int  row, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("removeRows");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("removeRows") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::removeRows(row, count, parent);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSqlRelationalTableModel::revert()
{
    QScriptValue _q_function = __qtscript_self.property("revert");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("revert") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlRelationalTableModel::revert();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSqlRelationalTableModel::revertRow(int  row)
{
    QScriptValue _q_function = __qtscript_self.property("revertRow");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("revertRow") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlRelationalTableModel::revertRow(row);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row));
        _q_function.setData(QScriptValue(false));
    }
}

QHash<int , QByteArray >  QtScriptShell_QSqlRelationalTableModel::roleNames() const
{
    QScriptValue _q_function = __qtscript_self.property("roleNames");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("roleNames") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::roleNames();
    } else {
        _q_function.setData(QScriptValue(true));
        QHash<int , QByteArray > _q_retval = qscriptvalue_cast<QHash<int , QByteArray > >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QSqlRelationalTableModel::rowCount(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("rowCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowCount") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::rowCount(parent);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::select()
{
    QScriptValue _q_function = __qtscript_self.property("select");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("select") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::select();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::selectRow(int  row)
{
    QScriptValue _q_function = __qtscript_self.property("selectRow");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectRow") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::selectRow(row);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QString  QtScriptShell_QSqlRelationalTableModel::selectStatement() const
{
    QScriptValue _q_function = __qtscript_self.property("selectStatement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectStatement") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::selectStatement();
    } else {
        _q_function.setData(QScriptValue(true));
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::setData(const QModelIndex&  item, const QVariant&  value, int  role)
{
    QScriptValue _q_function = __qtscript_self.property("setData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::setData(item, value, role);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, item)
            << qScriptValueFromValue(_q_engine, value)
            << qScriptValueFromValue(_q_engine, role)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSqlRelationalTableModel::setEditStrategy(QSqlTableModel::EditStrategy  strategy)
{
    QScriptValue _q_function = __qtscript_self.property("setEditStrategy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setEditStrategy") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlRelationalTableModel::setEditStrategy(strategy);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, strategy));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSqlRelationalTableModel::setFilter(const QString&  filter)
{
    QScriptValue _q_function = __qtscript_self.property("setFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlRelationalTableModel::setFilter(filter);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, filter));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::setHeaderData(int  section, Qt::Orientation  orientation, const QVariant&  value, int  role)
{
    QScriptValue _q_function = __qtscript_self.property("setHeaderData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setHeaderData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::setHeaderData(section, orientation, value, role);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, section)
            << qScriptValueFromValue(_q_engine, orientation)
            << qScriptValueFromValue(_q_engine, value)
            << qScriptValueFromValue(_q_engine, role)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::setItemData(const QModelIndex&  index, const QMap<int , QVariant >&  roles)
{
    QScriptValue _q_function = __qtscript_self.property("setItemData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setItemData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::setItemData(index, roles);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, roles)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSqlRelationalTableModel::setRelation(int  column, const QSqlRelation&  relation)
{
    QScriptValue _q_function = __qtscript_self.property("setRelation");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setRelation") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlRelationalTableModel::setRelation(column, relation);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, relation));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSqlRelationalTableModel::setSort(int  column, Qt::SortOrder  order)
{
    QScriptValue _q_function = __qtscript_self.property("setSort");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSort") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlRelationalTableModel::setSort(column, order);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, order));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSqlRelationalTableModel::setTable(const QString&  tableName)
{
    QScriptValue _q_function = __qtscript_self.property("setTable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setTable") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlRelationalTableModel::setTable(tableName);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, tableName));
        _q_function.setData(QScriptValue(false));
    }
}

QModelIndex  QtScriptShell_QSqlRelationalTableModel::sibling(int  row, int  column, const QModelIndex&  idx) const
{
    QScriptValue _q_function = __qtscript_self.property("sibling");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sibling") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::sibling(row, column, idx);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QModelIndex _q_retval = qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, idx)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSqlRelationalTableModel::sort(int  column, Qt::SortOrder  order)
{
    QScriptValue _q_function = __qtscript_self.property("sort");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sort") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlRelationalTableModel::sort(column, order);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, order));
        _q_function.setData(QScriptValue(false));
    }
}

QSize  QtScriptShell_QSqlRelationalTableModel::span(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("span");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("span") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::span(index);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::submit()
{
    QScriptValue _q_function = __qtscript_self.property("submit");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("submit") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::submit();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

Qt::DropActions  QtScriptShell_QSqlRelationalTableModel::supportedDragActions() const
{
    QScriptValue _q_function = __qtscript_self.property("supportedDragActions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("supportedDragActions") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::supportedDragActions();
    } else {
        _q_function.setData(QScriptValue(true));
        Qt::DropActions _q_retval = qscriptvalue_cast<Qt::DropActions >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

Qt::DropActions  QtScriptShell_QSqlRelationalTableModel::supportedDropActions() const
{
    QScriptValue _q_function = __qtscript_self.property("supportedDropActions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("supportedDropActions") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::supportedDropActions();
    } else {
        _q_function.setData(QScriptValue(true));
        Qt::DropActions _q_retval = qscriptvalue_cast<Qt::DropActions >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSqlRelationalTableModel::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlRelationalTableModel::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::updateRowInTable(int  row, const QSqlRecord&  values)
{
    QScriptValue _q_function = __qtscript_self.property("updateRowInTable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateRowInTable") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlRelationalTableModel::updateRowInTable(row, values);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, values)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

