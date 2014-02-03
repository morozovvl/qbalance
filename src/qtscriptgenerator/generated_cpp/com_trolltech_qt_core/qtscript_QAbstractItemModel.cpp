#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractitemmodel.h>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qdatastream.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qsize.h>
#include <qstringlist.h>
#include <qvector.h>

#include "qtscriptshell_QAbstractItemModel.h"

static const char * const qtscript_QAbstractItemModel_function_names[] = {
    "QAbstractItemModel"
    // static
    // prototype
    , "beginInsertColumns"
    , "beginInsertRows"
    , "beginMoveColumns"
    , "beginMoveRows"
    , "beginRemoveColumns"
    , "beginRemoveRows"
    , "beginResetModel"
    , "buddy"
    , "canDropMimeData"
    , "canFetchMore"
    , "changePersistentIndex"
    , "changePersistentIndexList"
    , "columnCount"
    , "createIndex"
    , "data"
    , "decodeData"
    , "dropMimeData"
    , "encodeData"
    , "endInsertColumns"
    , "endInsertRows"
    , "endMoveColumns"
    , "endMoveRows"
    , "endRemoveColumns"
    , "endRemoveRows"
    , "endResetModel"
    , "fetchMore"
    , "flags"
    , "hasChildren"
    , "hasIndex"
    , "headerData"
    , "index"
    , "insertColumn"
    , "insertColumns"
    , "insertRow"
    , "insertRows"
    , "itemData"
    , "match"
    , "mimeData"
    , "mimeTypes"
    , "moveColumn"
    , "moveColumns"
    , "moveRow"
    , "moveRows"
    , "parent"
    , "persistentIndexList"
    , "removeColumn"
    , "removeColumns"
    , "removeRow"
    , "removeRows"
    , "roleNames"
    , "rowCount"
    , "setData"
    , "setHeaderData"
    , "setItemData"
    , "sibling"
    , "sort"
    , "span"
    , "supportedDragActions"
    , "supportedDropActions"
    , "toString"
};

static const char * const qtscript_QAbstractItemModel_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "QModelIndex parent, int first, int last"
    , "QModelIndex parent, int first, int last"
    , "QModelIndex sourceParent, int sourceFirst, int sourceLast, QModelIndex destinationParent, int destinationColumn"
    , "QModelIndex sourceParent, int sourceFirst, int sourceLast, QModelIndex destinationParent, int destinationRow"
    , "QModelIndex parent, int first, int last"
    , "QModelIndex parent, int first, int last"
    , ""
    , "QModelIndex index"
    , "QMimeData data, DropAction action, int row, int column, QModelIndex parent"
    , "QModelIndex parent"
    , "QModelIndex from, QModelIndex to"
    , "List from, List to"
    , "QModelIndex parent"
    , "int row, int column, quintptr id\nint row, int column, void data"
    , "QModelIndex index, int role"
    , "int row, int column, QModelIndex parent, QDataStream stream"
    , "QMimeData data, DropAction action, int row, int column, QModelIndex parent"
    , "List indexes, QDataStream stream"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QModelIndex parent"
    , "QModelIndex index"
    , "QModelIndex parent"
    , "int row, int column, QModelIndex parent"
    , "int section, Orientation orientation, int role"
    , "int row, int column, QModelIndex parent"
    , "int column, QModelIndex parent"
    , "int column, int count, QModelIndex parent"
    , "int row, QModelIndex parent"
    , "int row, int count, QModelIndex parent"
    , "QModelIndex index"
    , "QModelIndex start, int role, Object value, int hits, MatchFlags flags"
    , "List indexes"
    , ""
    , "QModelIndex sourceParent, int sourceColumn, QModelIndex destinationParent, int destinationChild"
    , "QModelIndex sourceParent, int sourceColumn, int count, QModelIndex destinationParent, int destinationChild"
    , "QModelIndex sourceParent, int sourceRow, QModelIndex destinationParent, int destinationChild"
    , "QModelIndex sourceParent, int sourceRow, int count, QModelIndex destinationParent, int destinationChild"
    , "QModelIndex child"
    , ""
    , "int column, QModelIndex parent"
    , "int column, int count, QModelIndex parent"
    , "int row, QModelIndex parent"
    , "int row, int count, QModelIndex parent"
    , ""
    , "QModelIndex parent"
    , "QModelIndex index, Object value, int role"
    , "int section, Orientation orientation, Object value, int role"
    , "QModelIndex index, SortedMap roles"
    , "int row, int column, QModelIndex idx"
    , "int column, SortOrder order"
    , "QModelIndex index"
    , ""
    , ""
""
};

static const int qtscript_QAbstractItemModel_function_lengths[] = {
    1
    // static
    // prototype
    , 3
    , 3
    , 5
    , 5
    , 3
    , 3
    , 0
    , 1
    , 5
    , 1
    , 2
    , 2
    , 1
    , 3
    , 2
    , 4
    , 5
    , 2
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 3
    , 3
    , 3
    , 2
    , 3
    , 2
    , 3
    , 1
    , 5
    , 1
    , 0
    , 4
    , 5
    , 4
    , 5
    , 1
    , 0
    , 2
    , 3
    , 2
    , 3
    , 0
    , 1
    , 3
    , 4
    , 2
    , 3
    , 2
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QAbstractItemModel_prototype_call(QScriptContext *, QScriptEngine *);

class qtscript_QAbstractItemModel : public QAbstractItemModel
{
    friend QScriptValue qtscript_QAbstractItemModel_beginInsertColumns(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_beginInsertRows(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_beginMoveColumns(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_beginMoveRows(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_beginRemoveColumns(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_beginRemoveRows(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_beginResetModel(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_changePersistentIndex(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_changePersistentIndexList(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_createIndex(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_decodeData(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_encodeData(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_endInsertColumns(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_endInsertRows(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_endMoveColumns(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_endMoveRows(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_endRemoveColumns(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_endRemoveRows(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_endResetModel(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QAbstractItemModel_persistentIndexList(QScriptContext *, QScriptEngine *);

    friend QScriptValue qtscript_QAbstractItemModel_prototype_call(QScriptContext *, QScriptEngine *);

};

static QScriptValue qtscript_QAbstractItemModel_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractItemModel::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QAbstractItemModel_metaObject()
{
    return &QAbstractItemModel::staticMetaObject;
}

Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractItemModel*)
Q_DECLARE_METATYPE(QAbstractItemModel::LayoutChangeHint)
Q_DECLARE_METATYPE(QMimeData*)
Q_DECLARE_METATYPE(Qt::DropAction)
Q_DECLARE_METATYPE(QList<QModelIndex>)
Q_DECLARE_METATYPE(quintptr)
Q_DECLARE_METATYPE(QDataStream*)
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

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QAbstractItemModel::LayoutChangeHint
//

static const QAbstractItemModel::LayoutChangeHint qtscript_QAbstractItemModel_LayoutChangeHint_values[] = {
    QAbstractItemModel::NoLayoutChangeHint
    , QAbstractItemModel::VerticalSortHint
    , QAbstractItemModel::HorizontalSortHint
};

static const char * const qtscript_QAbstractItemModel_LayoutChangeHint_keys[] = {
    "NoLayoutChangeHint"
    , "VerticalSortHint"
    , "HorizontalSortHint"
};

static QString qtscript_QAbstractItemModel_LayoutChangeHint_toStringHelper(QAbstractItemModel::LayoutChangeHint value)
{
    const QMetaObject *meta = qtscript_QAbstractItemModel_metaObject();
    int idx = meta->indexOfEnumerator("LayoutChangeHint");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractItemModel_LayoutChangeHint_toScriptValue(QScriptEngine *engine, const QAbstractItemModel::LayoutChangeHint &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractItemModel"));
    return clazz.property(qtscript_QAbstractItemModel_LayoutChangeHint_toStringHelper(value));
}

static void qtscript_QAbstractItemModel_LayoutChangeHint_fromScriptValue(const QScriptValue &value, QAbstractItemModel::LayoutChangeHint &out)
{
    out = qvariant_cast<QAbstractItemModel::LayoutChangeHint>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractItemModel_LayoutChangeHint(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractItemModel_metaObject();
    int idx = meta->indexOfEnumerator("LayoutChangeHint");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractItemModel::LayoutChangeHint>(arg));
    return context->throwError(QString::fromLatin1("LayoutChangeHint(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractItemModel_LayoutChangeHint_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemModel::LayoutChangeHint value = qscriptvalue_cast<QAbstractItemModel::LayoutChangeHint>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractItemModel_LayoutChangeHint_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemModel::LayoutChangeHint value = qscriptvalue_cast<QAbstractItemModel::LayoutChangeHint>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractItemModel_LayoutChangeHint_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractItemModel_LayoutChangeHint_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractItemModel_LayoutChangeHint,
        qtscript_QAbstractItemModel_LayoutChangeHint_valueOf, qtscript_QAbstractItemModel_LayoutChangeHint_toString);
    qScriptRegisterMetaType<QAbstractItemModel::LayoutChangeHint>(engine, qtscript_QAbstractItemModel_LayoutChangeHint_toScriptValue,
        qtscript_QAbstractItemModel_LayoutChangeHint_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractItemModel_LayoutChangeHint_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractItemModel_LayoutChangeHint_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractItemModel
//

static QScriptValue qtscript_QAbstractItemModel_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 59;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    qtscript_QAbstractItemModel* _q_self = reinterpret_cast<qtscript_QAbstractItemModel*>(qscriptvalue_cast<QAbstractItemModel*>(context->thisObject()));
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractItemModel.%0(): this object is not a QAbstractItemModel")
            .arg(qtscript_QAbstractItemModel_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 3) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->beginInsertColumns(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 3) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->beginInsertRows(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 5) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QModelIndex _q_arg3 = qscriptvalue_cast<QModelIndex>(context->argument(3));
        int _q_arg4 = context->argument(4).toInt32();
        bool _q_result = _q_self->beginMoveColumns(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 5) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QModelIndex _q_arg3 = qscriptvalue_cast<QModelIndex>(context->argument(3));
        int _q_arg4 = context->argument(4).toInt32();
        bool _q_result = _q_self->beginMoveRows(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 3) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->beginRemoveColumns(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 3) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->beginRemoveRows(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        _q_self->beginResetModel();
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_result = _q_self->buddy(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 5) {
        QMimeData* _q_arg0 = qscriptvalue_cast<QMimeData*>(context->argument(0));
        Qt::DropAction _q_arg1 = qscriptvalue_cast<Qt::DropAction>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QModelIndex _q_arg4 = qscriptvalue_cast<QModelIndex>(context->argument(4));
        bool _q_result = _q_self->canDropMimeData(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        bool _q_result = _q_self->canFetchMore(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        _q_self->changePersistentIndex(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        QList<QModelIndex> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QList<QModelIndex> _q_arg1;
        qScriptValueToSequence(context->argument(1), _q_arg1);
        _q_self->changePersistentIndexList(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->columnCount();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_result = _q_self->columnCount(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_result = _q_self->createIndex(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && (qMetaTypeId<quintptr>() == context->argument(2).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            quintptr _q_arg2 = qscriptvalue_cast<quintptr>(context->argument(2));
            QModelIndex _q_result = _q_self->createIndex(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && qscriptvalue_cast<void*>(context->argument(2))) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            void* _q_arg2 = qscriptvalue_cast<void*>(context->argument(2));
            QModelIndex _q_result = _q_self->createIndex(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QVariant _q_result = _q_self->data(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QVariant _q_result = _q_self->data(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));

        QDataStream & _q_arg3 = *qscriptvalue_cast<QDataStream*>(context->argument(3));
                bool _q_result = _q_self->decodeData(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 5) {
        QMimeData* _q_arg0 = qscriptvalue_cast<QMimeData*>(context->argument(0));
        Qt::DropAction _q_arg1 = qscriptvalue_cast<Qt::DropAction>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QModelIndex _q_arg4 = qscriptvalue_cast<QModelIndex>(context->argument(4));
        bool _q_result = _q_self->dropMimeData(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 2) {
        QList<QModelIndex> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);

        QDataStream & _q_arg1 = *qscriptvalue_cast<QDataStream*>(context->argument(1));
                _q_self->encodeData(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        _q_self->endInsertColumns();
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        _q_self->endInsertRows();
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        _q_self->endMoveColumns();
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        _q_self->endMoveRows();
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        _q_self->endRemoveColumns();
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        _q_self->endRemoveRows();
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        _q_self->endResetModel();
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        _q_self->fetchMore(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QFlags<Qt::ItemFlag> _q_result = _q_self->flags(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasChildren();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        bool _q_result = _q_self->hasChildren(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->hasIndex(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        bool _q_result = _q_self->hasIndex(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::Orientation _q_arg1 = qscriptvalue_cast<Qt::Orientation>(context->argument(1));
        QVariant _q_result = _q_self->headerData(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::Orientation _q_arg1 = qscriptvalue_cast<Qt::Orientation>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QVariant _q_result = _q_self->headerData(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_result = _q_self->index(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        QModelIndex _q_result = _q_self->index(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->insertColumn(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_result = _q_self->insertColumn(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->insertColumns(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        bool _q_result = _q_self->insertColumns(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->insertRow(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_result = _q_self->insertRow(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->insertRows(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        bool _q_result = _q_self->insertRows(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QMap<int,QVariant> _q_result = _q_self->itemData(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 3) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QVariant _q_arg2 = context->argument(2).toVariant();
        QList<QModelIndex> _q_result = _q_self->match(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QVariant _q_arg2 = context->argument(2).toVariant();
        int _q_arg3 = context->argument(3).toInt32();
        QList<QModelIndex> _q_result = _q_self->match(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QVariant _q_arg2 = context->argument(2).toVariant();
        int _q_arg3 = context->argument(3).toInt32();
        QFlags<Qt::MatchFlag> _q_arg4 = qscriptvalue_cast<QFlags<Qt::MatchFlag> >(context->argument(4));
        QList<QModelIndex> _q_result = _q_self->match(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        QList<QModelIndex> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QMimeData* _q_result = _q_self->mimeData(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 38:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->mimeTypes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 39:
    if (context->argumentCount() == 4) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        int _q_arg3 = context->argument(3).toInt32();
        bool _q_result = _q_self->moveColumn(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 40:
    if (context->argumentCount() == 5) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QModelIndex _q_arg3 = qscriptvalue_cast<QModelIndex>(context->argument(3));
        int _q_arg4 = context->argument(4).toInt32();
        bool _q_result = _q_self->moveColumns(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 41:
    if (context->argumentCount() == 4) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        int _q_arg3 = context->argument(3).toInt32();
        bool _q_result = _q_self->moveRow(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 42:
    if (context->argumentCount() == 5) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QModelIndex _q_arg3 = qscriptvalue_cast<QModelIndex>(context->argument(3));
        int _q_arg4 = context->argument(4).toInt32();
        bool _q_result = _q_self->moveRows(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 43:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_result = _q_self->parent(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 44:
    if (context->argumentCount() == 0) {
        QList<QModelIndex> _q_result = _q_self->persistentIndexList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->removeColumn(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_result = _q_self->removeColumn(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 46:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->removeColumns(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        bool _q_result = _q_self->removeColumns(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 47:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->removeRow(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_result = _q_self->removeRow(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 48:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->removeRows(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        bool _q_result = _q_self->removeRows(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 49:
    if (context->argumentCount() == 0) {
        QHash<int,QByteArray> _q_result = _q_self->roleNames();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 50:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->rowCount();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_result = _q_self->rowCount(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 51:
    if (context->argumentCount() == 2) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        bool _q_result = _q_self->setData(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        int _q_arg2 = context->argument(2).toInt32();
        bool _q_result = _q_self->setData(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 52:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::Orientation _q_arg1 = qscriptvalue_cast<Qt::Orientation>(context->argument(1));
        QVariant _q_arg2 = context->argument(2).toVariant();
        bool _q_result = _q_self->setHeaderData(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::Orientation _q_arg1 = qscriptvalue_cast<Qt::Orientation>(context->argument(1));
        QVariant _q_arg2 = context->argument(2).toVariant();
        int _q_arg3 = context->argument(3).toInt32();
        bool _q_result = _q_self->setHeaderData(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 53:
    if (context->argumentCount() == 2) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QMap<int,QVariant> _q_arg1 = qscriptvalue_cast<QMap<int,QVariant> >(context->argument(1));
        bool _q_result = _q_self->setItemData(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 54:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        QModelIndex _q_result = _q_self->sibling(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 55:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->sort(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::SortOrder _q_arg1 = qscriptvalue_cast<Qt::SortOrder>(context->argument(1));
        _q_self->sort(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 56:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QSize _q_result = _q_self->span(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 57:
    if (context->argumentCount() == 0) {
        QFlags<Qt::DropAction> _q_result = _q_self->supportedDragActions();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 58:
    if (context->argumentCount() == 0) {
        QFlags<Qt::DropAction> _q_result = _q_self->supportedDropActions();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 59: {
    QString result = QString::fromLatin1("QAbstractItemModel");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractItemModel_throw_ambiguity_error_helper(context,
        qtscript_QAbstractItemModel_function_names[_id+1],
        qtscript_QAbstractItemModel_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractItemModel_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractItemModel(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractItemModel* _q_cpp_result = new QtScriptShell_QAbstractItemModel();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractItemModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QAbstractItemModel* _q_cpp_result = new QtScriptShell_QAbstractItemModel(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractItemModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractItemModel_throw_ambiguity_error_helper(context,
        qtscript_QAbstractItemModel_function_names[_id],
        qtscript_QAbstractItemModel_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractItemModel_toScriptValue(QScriptEngine *engine, QAbstractItemModel* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractItemModel_fromScriptValue(const QScriptValue &value, QAbstractItemModel* &out)
{
    out = qobject_cast<QAbstractItemModel*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractItemModel_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractItemModel*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractItemModel*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 60; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractItemModel_prototype_call, qtscript_QAbstractItemModel_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractItemModel_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractItemModel*>(engine, qtscript_QAbstractItemModel_toScriptValue, 
        qtscript_QAbstractItemModel_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractItemModel_static_call, proto, qtscript_QAbstractItemModel_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("LayoutChangeHint"),
        qtscript_create_QAbstractItemModel_LayoutChangeHint_class(engine, ctor));
    return ctor;
}
