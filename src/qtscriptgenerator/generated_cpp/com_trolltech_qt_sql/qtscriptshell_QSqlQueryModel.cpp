#include "qtscriptshell_QSqlQueryModel.h"

#include <QtScript/QScriptEngine>
#include <QSize>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
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
#include <qsqlquery.h>
#include <qsqlrecord.h>
#include <qstringlist.h>
#include <qvector.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QMimeData*)
Q_DECLARE_METATYPE(Qt::DropAction)
Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::ItemFlag>)
Q_DECLARE_METATYPE(Qt::Orientation)
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
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QFlags<Qt::DropAction>)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QSqlQueryModel::QtScriptShell_QSqlQueryModel(QObject*  parent)
    : QSqlQueryModel(parent) {}

QtScriptShell_QSqlQueryModel::~QtScriptShell_QSqlQueryModel() {}

QModelIndex  QtScriptShell_QSqlQueryModel::buddy(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("buddy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("buddy") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::buddy(index);
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

bool  QtScriptShell_QSqlQueryModel::canDropMimeData(const QMimeData*  data, Qt::DropAction  action, int  row, int  column, const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("canDropMimeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canDropMimeData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::canDropMimeData(data, action, row, column, parent);
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

bool  QtScriptShell_QSqlQueryModel::canFetchMore(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("canFetchMore");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canFetchMore") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::canFetchMore(parent);
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

void QtScriptShell_QSqlQueryModel::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlQueryModel::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QSqlQueryModel::clear()
{
    QScriptValue _q_function = __qtscript_self.property("clear");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("clear") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlQueryModel::clear();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

int  QtScriptShell_QSqlQueryModel::columnCount(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("columnCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("columnCount") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::columnCount(parent);
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

void QtScriptShell_QSqlQueryModel::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlQueryModel::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

QVariant  QtScriptShell_QSqlQueryModel::data(const QModelIndex&  item, int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::data(item, role);
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

bool  QtScriptShell_QSqlQueryModel::dropMimeData(const QMimeData*  data, Qt::DropAction  action, int  row, int  column, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("dropMimeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dropMimeData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::dropMimeData(data, action, row, column, parent);
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

bool  QtScriptShell_QSqlQueryModel::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::event(arg__1);
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

bool  QtScriptShell_QSqlQueryModel::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::eventFilter(arg__1, arg__2);
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

void QtScriptShell_QSqlQueryModel::fetchMore(const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("fetchMore");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchMore") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlQueryModel::fetchMore(parent);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent));
        _q_function.setData(QScriptValue(false));
    }
}

Qt::ItemFlags  QtScriptShell_QSqlQueryModel::flags(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("flags");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("flags") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::flags(index);
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

QVariant  QtScriptShell_QSqlQueryModel::headerData(int  section, Qt::Orientation  orientation, int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("headerData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("headerData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::headerData(section, orientation, role);
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

QModelIndex  QtScriptShell_QSqlQueryModel::index(int  row, int  column, const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("index");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("index") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::index(row, column, parent);
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

QModelIndex  QtScriptShell_QSqlQueryModel::indexInQuery(const QModelIndex&  item) const
{
    QScriptValue _q_function = __qtscript_self.property("indexInQuery");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexInQuery") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::indexInQuery(item);
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

bool  QtScriptShell_QSqlQueryModel::insertColumns(int  column, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("insertColumns");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertColumns") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::insertColumns(column, count, parent);
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

bool  QtScriptShell_QSqlQueryModel::insertRows(int  row, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("insertRows");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertRows") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::insertRows(row, count, parent);
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

QMap<int , QVariant >  QtScriptShell_QSqlQueryModel::itemData(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("itemData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::itemData(index);
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

QList<QModelIndex >  QtScriptShell_QSqlQueryModel::match(const QModelIndex&  start, int  role, const QVariant&  value, int  hits, Qt::MatchFlags  flags) const
{
    QScriptValue _q_function = __qtscript_self.property("match");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("match") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::match(start, role, value, hits, flags);
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

QMimeData*  QtScriptShell_QSqlQueryModel::mimeData(const QList<QModelIndex >&  indexes) const
{
    QScriptValue _q_function = __qtscript_self.property("mimeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mimeData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::mimeData(indexes);
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

QStringList  QtScriptShell_QSqlQueryModel::mimeTypes() const
{
    QScriptValue _q_function = __qtscript_self.property("mimeTypes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mimeTypes") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::mimeTypes();
    } else {
        _q_function.setData(QScriptValue(true));
        QStringList _q_retval = qscriptvalue_cast<QStringList >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlQueryModel::moveColumns(const QModelIndex&  sourceParent, int  sourceColumn, int  count, const QModelIndex&  destinationParent, int  destinationChild)
{
    QScriptValue _q_function = __qtscript_self.property("moveColumns");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("moveColumns") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::moveColumns(sourceParent, sourceColumn, count, destinationParent, destinationChild);
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

bool  QtScriptShell_QSqlQueryModel::moveRows(const QModelIndex&  sourceParent, int  sourceRow, int  count, const QModelIndex&  destinationParent, int  destinationChild)
{
    QScriptValue _q_function = __qtscript_self.property("moveRows");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("moveRows") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::moveRows(sourceParent, sourceRow, count, destinationParent, destinationChild);
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

void QtScriptShell_QSqlQueryModel::queryChange()
{
    QScriptValue _q_function = __qtscript_self.property("queryChange");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("queryChange") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlQueryModel::queryChange();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QSqlQueryModel::removeColumns(int  column, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("removeColumns");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("removeColumns") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::removeColumns(column, count, parent);
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

bool  QtScriptShell_QSqlQueryModel::removeRows(int  row, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("removeRows");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("removeRows") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::removeRows(row, count, parent);
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

void QtScriptShell_QSqlQueryModel::revert()
{
    QScriptValue _q_function = __qtscript_self.property("revert");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("revert") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlQueryModel::revert();
    } else {
        _q_function.setData(QScriptValue(true));
        _q_function.call(__qtscript_self);
        _q_function.setData(QScriptValue(false));
    }
}

QHash<int , QByteArray >  QtScriptShell_QSqlQueryModel::roleNames() const
{
    QScriptValue _q_function = __qtscript_self.property("roleNames");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("roleNames") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::roleNames();
    } else {
        _q_function.setData(QScriptValue(true));
        QHash<int , QByteArray > _q_retval = qscriptvalue_cast<QHash<int , QByteArray > >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QSqlQueryModel::rowCount(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("rowCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowCount") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::rowCount(parent);
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

bool  QtScriptShell_QSqlQueryModel::setData(const QModelIndex&  index, const QVariant&  value, int  role)
{
    QScriptValue _q_function = __qtscript_self.property("setData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::setData(index, value, role);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, value)
            << qScriptValueFromValue(_q_engine, role)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QSqlQueryModel::setHeaderData(int  section, Qt::Orientation  orientation, const QVariant&  value, int  role)
{
    QScriptValue _q_function = __qtscript_self.property("setHeaderData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setHeaderData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::setHeaderData(section, orientation, value, role);
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

bool  QtScriptShell_QSqlQueryModel::setItemData(const QModelIndex&  index, const QMap<int , QVariant >&  roles)
{
    QScriptValue _q_function = __qtscript_self.property("setItemData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setItemData") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::setItemData(index, roles);
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

QModelIndex  QtScriptShell_QSqlQueryModel::sibling(int  row, int  column, const QModelIndex&  idx) const
{
    QScriptValue _q_function = __qtscript_self.property("sibling");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sibling") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::sibling(row, column, idx);
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

void QtScriptShell_QSqlQueryModel::sort(int  column, Qt::SortOrder  order)
{
    QScriptValue _q_function = __qtscript_self.property("sort");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sort") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlQueryModel::sort(column, order);
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

QSize  QtScriptShell_QSqlQueryModel::span(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("span");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("span") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::span(index);
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

bool  QtScriptShell_QSqlQueryModel::submit()
{
    QScriptValue _q_function = __qtscript_self.property("submit");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("submit") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::submit();
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

Qt::DropActions  QtScriptShell_QSqlQueryModel::supportedDragActions() const
{
    QScriptValue _q_function = __qtscript_self.property("supportedDragActions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("supportedDragActions") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::supportedDragActions();
    } else {
        _q_function.setData(QScriptValue(true));
        Qt::DropActions _q_retval = qscriptvalue_cast<Qt::DropActions >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

Qt::DropActions  QtScriptShell_QSqlQueryModel::supportedDropActions() const
{
    QScriptValue _q_function = __qtscript_self.property("supportedDropActions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("supportedDropActions") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QSqlQueryModel::supportedDropActions();
    } else {
        _q_function.setData(QScriptValue(true));
        Qt::DropActions _q_retval = qscriptvalue_cast<Qt::DropActions >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QSqlQueryModel::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QSqlQueryModel::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

