#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsyntaxhighlighter.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qfont.h>
#include <qlist.h>
#include <qobject.h>
#include <qsyntaxhighlighter.h>
#include <qtextdocument.h>
#include <qtextformat.h>
#include <qtextobject.h>

#include "qtscriptshell_QSyntaxHighlighter.h"

static const char * const qtscript_QSyntaxHighlighter_function_names[] = {
    "QSyntaxHighlighter"
    // static
    // prototype
    , "currentBlock"
    , "currentBlockState"
    , "currentBlockUserData"
    , "document"
    , "format"
    , "highlightBlock"
    , "previousBlockState"
    , "setCurrentBlockState"
    , "setCurrentBlockUserData"
    , "setDocument"
    , "setFormat"
    , "toString"
};

static const char * const qtscript_QSyntaxHighlighter_function_signatures[] = {
    "QObject parent\nQTextDocument parent"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "int pos"
    , "String text"
    , ""
    , "int newState"
    , "QTextBlockUserData data"
    , "QTextDocument doc"
    , "int start, int count, QColor color\nint start, int count, QFont font\nint start, int count, QTextCharFormat format"
""
};

static const int qtscript_QSyntaxHighlighter_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 3
    , 0
};

static QScriptValue qtscript_QSyntaxHighlighter_prototype_call(QScriptContext *, QScriptEngine *);

class qtscript_QSyntaxHighlighter : public QSyntaxHighlighter
{
    friend QScriptValue qtscript_QSyntaxHighlighter_currentBlock(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSyntaxHighlighter_currentBlockState(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSyntaxHighlighter_currentBlockUserData(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSyntaxHighlighter_format(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSyntaxHighlighter_highlightBlock(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSyntaxHighlighter_previousBlockState(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSyntaxHighlighter_setCurrentBlockState(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSyntaxHighlighter_setCurrentBlockUserData(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QSyntaxHighlighter_setFormat(QScriptContext *, QScriptEngine *);

    friend QScriptValue qtscript_QSyntaxHighlighter_prototype_call(QScriptContext *, QScriptEngine *);

};

static QScriptValue qtscript_QSyntaxHighlighter_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSyntaxHighlighter::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSyntaxHighlighter*)
Q_DECLARE_METATYPE(QtScriptShell_QSyntaxHighlighter*)
Q_DECLARE_METATYPE(QTextBlock)
Q_DECLARE_METATYPE(QTextBlockUserData*)
Q_DECLARE_METATYPE(QTextDocument*)
Q_DECLARE_METATYPE(QTextCharFormat)

//
// QSyntaxHighlighter
//

static QScriptValue qtscript_QSyntaxHighlighter_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 11;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    qtscript_QSyntaxHighlighter* _q_self = reinterpret_cast<qtscript_QSyntaxHighlighter*>(qscriptvalue_cast<QSyntaxHighlighter*>(context->thisObject()));
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSyntaxHighlighter.%0(): this object is not a QSyntaxHighlighter")
            .arg(qtscript_QSyntaxHighlighter_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QTextBlock _q_result = _q_self->currentBlock();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentBlockState();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QTextBlockUserData* _q_result = _q_self->currentBlockUserData();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QTextDocument* _q_result = _q_self->document();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QTextCharFormat _q_result = _q_self->format(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->highlightBlock(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->previousBlockState();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setCurrentBlockState(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QTextBlockUserData* _q_arg0 = qscriptvalue_cast<QTextBlockUserData*>(context->argument(0));
        _q_self->setCurrentBlockUserData(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QTextDocument* _q_arg0 = qscriptvalue_cast<QTextDocument*>(context->argument(0));
        _q_self->setDocument(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 3) {
        if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && (qMetaTypeId<QColor>() == context->argument(2).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QColor _q_arg2 = qscriptvalue_cast<QColor>(context->argument(2));
            _q_self->setFormat(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && (qMetaTypeId<QFont>() == context->argument(2).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QFont _q_arg2 = qscriptvalue_cast<QFont>(context->argument(2));
            _q_self->setFormat(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && (qMetaTypeId<QTextCharFormat>() == context->argument(2).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QTextCharFormat _q_arg2 = qscriptvalue_cast<QTextCharFormat>(context->argument(2));
            _q_self->setFormat(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 11: {
    QString result = QString::fromLatin1("QSyntaxHighlighter");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSyntaxHighlighter_throw_ambiguity_error_helper(context,
        qtscript_QSyntaxHighlighter_function_names[_id+1],
        qtscript_QSyntaxHighlighter_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSyntaxHighlighter_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSyntaxHighlighter(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QSyntaxHighlighter* _q_cpp_result = new QtScriptShell_QSyntaxHighlighter(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSyntaxHighlighter*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QTextDocument*>(context->argument(0))) {
            QTextDocument* _q_arg0 = qscriptvalue_cast<QTextDocument*>(context->argument(0));
            QtScriptShell_QSyntaxHighlighter* _q_cpp_result = new QtScriptShell_QSyntaxHighlighter(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSyntaxHighlighter*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSyntaxHighlighter_throw_ambiguity_error_helper(context,
        qtscript_QSyntaxHighlighter_function_names[_id],
        qtscript_QSyntaxHighlighter_function_signatures[_id]);
}

static QScriptValue qtscript_QSyntaxHighlighter_toScriptValue(QScriptEngine *engine, QSyntaxHighlighter* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSyntaxHighlighter_fromScriptValue(const QScriptValue &value, QSyntaxHighlighter* &out)
{
    out = qobject_cast<QSyntaxHighlighter*>(value.toQObject());
}

QScriptValue qtscript_create_QSyntaxHighlighter_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSyntaxHighlighter*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSyntaxHighlighter*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 12; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSyntaxHighlighter_prototype_call, qtscript_QSyntaxHighlighter_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSyntaxHighlighter_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSyntaxHighlighter*>(engine, qtscript_QSyntaxHighlighter_toScriptValue, 
        qtscript_QSyntaxHighlighter_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSyntaxHighlighter_static_call, proto, qtscript_QSyntaxHighlighter_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
