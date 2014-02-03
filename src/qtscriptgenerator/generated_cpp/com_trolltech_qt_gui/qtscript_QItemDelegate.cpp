#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qitemdelegate.h>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qfont.h>
#include <qitemdelegate.h>
#include <qitemeditorfactory.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qrect.h>
#include <qsize.h>
#include <qstyleoption.h>
#include <qvector.h>
#include <qwidget.h>

#include "qtscriptshell_QItemDelegate.h"

static const char * const qtscript_QItemDelegate_function_names[] = {
    "QItemDelegate"
    // static
    // prototype
    , "decoration"
    , "doCheck"
    , "drawBackground"
    , "drawCheck"
    , "drawDecoration"
    , "drawDisplay"
    , "drawFocus"
    , "itemEditorFactory"
    , "rect"
    , "setItemEditorFactory"
    , "setOptions"
    , "textRectangle"
    , "toString"
};

static const char * const qtscript_QItemDelegate_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "QStyleOptionViewItem option, Object variant"
    , "QStyleOptionViewItem option, QRect bounding, Object variant"
    , "QPainter painter, QStyleOptionViewItem option, QModelIndex index"
    , "QPainter painter, QStyleOptionViewItem option, QRect rect, CheckState state"
    , "QPainter painter, QStyleOptionViewItem option, QRect rect, QPixmap pixmap"
    , "QPainter painter, QStyleOptionViewItem option, QRect rect, String text"
    , "QPainter painter, QStyleOptionViewItem option, QRect rect"
    , ""
    , "QStyleOptionViewItem option, QModelIndex index, int role"
    , "QItemEditorFactory factory"
    , "QModelIndex index, QStyleOptionViewItem option"
    , "QPainter painter, QRect rect, QFont font, String text"
""
};

static const int qtscript_QItemDelegate_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 3
    , 3
    , 4
    , 4
    , 4
    , 3
    , 0
    , 3
    , 1
    , 2
    , 4
    , 0
};

static QScriptValue qtscript_QItemDelegate_prototype_call(QScriptContext *, QScriptEngine *);

class qtscript_QItemDelegate : public QItemDelegate
{
    friend QScriptValue qtscript_QItemDelegate_decoration(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QItemDelegate_doCheck(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QItemDelegate_drawBackground(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QItemDelegate_drawCheck(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QItemDelegate_drawDecoration(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QItemDelegate_drawDisplay(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QItemDelegate_drawFocus(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QItemDelegate_rect(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QItemDelegate_setOptions(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QItemDelegate_textRectangle(QScriptContext *, QScriptEngine *);

    friend QScriptValue qtscript_QItemDelegate_prototype_call(QScriptContext *, QScriptEngine *);

};

static QScriptValue qtscript_QItemDelegate_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QItemDelegate::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QItemDelegate*)
Q_DECLARE_METATYPE(QtScriptShell_QItemDelegate*)
Q_DECLARE_METATYPE(QStyleOptionViewItem)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(Qt::CheckState)
Q_DECLARE_METATYPE(QItemEditorFactory*)
Q_DECLARE_METATYPE(QAbstractItemDelegate*)

//
// QItemDelegate
//

static QScriptValue qtscript_QItemDelegate_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 12;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    qtscript_QItemDelegate* _q_self = reinterpret_cast<qtscript_QItemDelegate*>(qscriptvalue_cast<QItemDelegate*>(context->thisObject()));
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QItemDelegate.%0(): this object is not a QItemDelegate")
            .arg(qtscript_QItemDelegate_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QStyleOptionViewItem _q_arg0 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        QPixmap _q_result = _q_self->decoration(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 3) {
        QStyleOptionViewItem _q_arg0 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(0));
        QRect _q_arg1 = qscriptvalue_cast<QRect>(context->argument(1));
        QVariant _q_arg2 = context->argument(2).toVariant();
        QRect _q_result = _q_self->doCheck(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 3) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QStyleOptionViewItem _q_arg1 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(1));
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        _q_self->drawBackground(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 4) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QStyleOptionViewItem _q_arg1 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(1));
        QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
        Qt::CheckState _q_arg3 = qscriptvalue_cast<Qt::CheckState>(context->argument(3));
        _q_self->drawCheck(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 4) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QStyleOptionViewItem _q_arg1 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(1));
        QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
        QPixmap _q_arg3 = qscriptvalue_cast<QPixmap>(context->argument(3));
        _q_self->drawDecoration(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 4) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QStyleOptionViewItem _q_arg1 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(1));
        QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
        QString _q_arg3 = context->argument(3).toString();
        _q_self->drawDisplay(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 3) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QStyleOptionViewItem _q_arg1 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(1));
        QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
        _q_self->drawFocus(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QItemEditorFactory* _q_result = _q_self->itemEditorFactory();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 3) {
        QStyleOptionViewItem _q_arg0 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(0));
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QRect _q_result = _q_self->rect(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QItemEditorFactory* _q_arg0 = qscriptvalue_cast<QItemEditorFactory*>(context->argument(0));
        _q_self->setItemEditorFactory(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QStyleOptionViewItem _q_arg1 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(1));
        QStyleOptionViewItem _q_result = _q_self->setOptions(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 4) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRect _q_arg1 = qscriptvalue_cast<QRect>(context->argument(1));
        QFont _q_arg2 = qscriptvalue_cast<QFont>(context->argument(2));
        QString _q_arg3 = context->argument(3).toString();
        QRect _q_result = _q_self->textRectangle(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12: {
    QString result = QString::fromLatin1("QItemDelegate");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QItemDelegate_throw_ambiguity_error_helper(context,
        qtscript_QItemDelegate_function_names[_id+1],
        qtscript_QItemDelegate_function_signatures[_id+1]);
}

static QScriptValue qtscript_QItemDelegate_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QItemDelegate(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QItemDelegate* _q_cpp_result = new QtScriptShell_QItemDelegate();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QItemDelegate*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QItemDelegate* _q_cpp_result = new QtScriptShell_QItemDelegate(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QItemDelegate*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QItemDelegate_throw_ambiguity_error_helper(context,
        qtscript_QItemDelegate_function_names[_id],
        qtscript_QItemDelegate_function_signatures[_id]);
}

static QScriptValue qtscript_QItemDelegate_toScriptValue(QScriptEngine *engine, QItemDelegate* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QItemDelegate_fromScriptValue(const QScriptValue &value, QItemDelegate* &out)
{
    out = qobject_cast<QItemDelegate*>(value.toQObject());
}

QScriptValue qtscript_create_QItemDelegate_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QItemDelegate*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QItemDelegate*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractItemDelegate*>()));
    for (int i = 0; i < 13; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QItemDelegate_prototype_call, qtscript_QItemDelegate_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QItemDelegate_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QItemDelegate*>(engine, qtscript_QItemDelegate_toScriptValue, 
        qtscript_QItemDelegate_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QItemDelegate_static_call, proto, qtscript_QItemDelegate_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
