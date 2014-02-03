#include "qtscriptshell_QAccessibleInterface.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qaccessible.h>
#include <qobject.h>
#include <qpair.h>
#include <qrect.h>
#include <qvector.h>
#include <qwindow.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QAccessibleInterface*)
Q_DECLARE_METATYPE(QAccessible::InterfaceType)
Q_DECLARE_METATYPE(QFlags<QAccessible::RelationFlag>)
#if QT_VERSION < 0x050000
template <> \
struct QMetaTypeId< QPair<QAccessibleInterface*,QFlags<QAccessible::RelationFlag> > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QPair<QAccessibleInterface*,QFlags<QAccessible::RelationFlag> > >("QPair<QAccessibleInterface*,QFlags<QAccessible::RelationFlag> >"); \
        return metatype_id; \
    } \
};
#else // QT_VERSION < 0x050000
template <> \
struct QMetaTypeId< QPair<QAccessibleInterface*,QFlags<QAccessible::RelationFlag> > >
{
    enum { Defined = 1 };
    static int qt_metatype_id()
    {
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);
        if (const int id = metatype_id.loadAcquire())
            return id;
        const int newId = qRegisterMetaType< QPair<QAccessibleInterface*,QFlags<QAccessible::RelationFlag> > >("QPair<QAccessibleInterface*,QFlags<QAccessible::RelationFlag> >", reinterpret_cast< QPair<QAccessibleInterface*,QFlags<QAccessible::RelationFlag> > *>(quintptr(-1)));
        metatype_id.storeRelease(newId);
        return newId;
    }
};
#endif
#if QT_VERSION < 0x050000
template <> \
struct QMetaTypeId< QVector<QPair<QAccessibleInterface*,QFlags<QAccessible::RelationFlag> > > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QVector<QPair<QAccessibleInterface*,QFlags<QAccessible::RelationFlag> > > >("QVector<QPair<QAccessibleInterface*,QFlags<QAccessible::RelationFlag> > >"); \
        return metatype_id; \
    } \
};
#else // QT_VERSION < 0x050000
template <> \
struct QMetaTypeId< QVector<QPair<QAccessibleInterface*,QFlags<QAccessible::RelationFlag> > > >
{
    enum { Defined = 1 };
    static int qt_metatype_id()
    {
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);
        if (const int id = metatype_id.loadAcquire())
            return id;
        const int newId = qRegisterMetaType< QVector<QPair<QAccessibleInterface*,QFlags<QAccessible::RelationFlag> > > >("QVector<QPair<QAccessibleInterface*,QFlags<QAccessible::RelationFlag> > >", reinterpret_cast< QVector<QPair<QAccessibleInterface*,QFlags<QAccessible::RelationFlag> > > *>(quintptr(-1)));
        metatype_id.storeRelease(newId);
        return newId;
    }
};
#endif
Q_DECLARE_METATYPE(QAccessible::Role)
Q_DECLARE_METATYPE(QAccessible::Text)
Q_DECLARE_METATYPE(QAccessible::State)
Q_DECLARE_METATYPE(QWindow*)

QtScriptShell_QAccessibleInterface::QtScriptShell_QAccessibleInterface()
    : QAccessibleInterface() {}

QtScriptShell_QAccessibleInterface::~QtScriptShell_QAccessibleInterface() {}

QAccessibleInterface*  QtScriptShell_QAccessibleInterface::child(int  index) const
{
    QScriptValue _q_function = __qtscript_self.property("child");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("child") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAccessibleInterface::child() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QAccessibleInterface* _q_retval = qscriptvalue_cast<QAccessibleInterface* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QAccessibleInterface*  QtScriptShell_QAccessibleInterface::childAt(int  x, int  y) const
{
    QScriptValue _q_function = __qtscript_self.property("childAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childAt") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAccessibleInterface::childAt() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QAccessibleInterface* _q_retval = qscriptvalue_cast<QAccessibleInterface* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, x)
            << qScriptValueFromValue(_q_engine, y)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QAccessibleInterface::childCount() const
{
    QScriptValue _q_function = __qtscript_self.property("childCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childCount") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAccessibleInterface::childCount() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QAccessibleInterface*  QtScriptShell_QAccessibleInterface::focusChild() const
{
    QScriptValue _q_function = __qtscript_self.property("focusChild");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusChild") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QAccessibleInterface::focusChild();
    } else {
        _q_function.setData(QScriptValue(true));
        QAccessibleInterface* _q_retval = qscriptvalue_cast<QAccessibleInterface* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QAccessibleInterface::indexOfChild(const QAccessibleInterface*  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("indexOfChild");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexOfChild") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAccessibleInterface::indexOfChild() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QAccessibleInterface *>(arg__1))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void*  QtScriptShell_QAccessibleInterface::interface_cast(QAccessible::InterfaceType  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("interface_cast");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("interface_cast") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QAccessibleInterface::interface_cast(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        void* _q_retval = qscriptvalue_cast<void* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

bool  QtScriptShell_QAccessibleInterface::isValid() const
{
    QScriptValue _q_function = __qtscript_self.property("isValid");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isValid") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAccessibleInterface::isValid() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        bool _q_retval = qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QObject*  QtScriptShell_QAccessibleInterface::object() const
{
    QScriptValue _q_function = __qtscript_self.property("object");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("object") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAccessibleInterface::object() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QObject* _q_retval = qscriptvalue_cast<QObject* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QAccessibleInterface*  QtScriptShell_QAccessibleInterface::parent() const
{
    QScriptValue _q_function = __qtscript_self.property("parent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAccessibleInterface::parent() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QAccessibleInterface* _q_retval = qscriptvalue_cast<QAccessibleInterface* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QRect  QtScriptShell_QAccessibleInterface::rect() const
{
    QScriptValue _q_function = __qtscript_self.property("rect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rect") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAccessibleInterface::rect() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QRect _q_retval = qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QVector<QPair<QAccessibleInterface* , QAccessible::Relation >  >  QtScriptShell_QAccessibleInterface::relations(QAccessible::Relation  match) const
{
    QScriptValue _q_function = __qtscript_self.property("relations");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("relations") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QAccessibleInterface::relations(match);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QVector<QPair<QAccessibleInterface* , QAccessible::Relation >  > _q_retval = qscriptvalue_cast<QVector<QPair<QAccessibleInterface* , QAccessible::Relation >  > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, match)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QAccessible::Role  QtScriptShell_QAccessibleInterface::role() const
{
    QScriptValue _q_function = __qtscript_self.property("role");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("role") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAccessibleInterface::role() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QAccessible::Role _q_retval = qscriptvalue_cast<QAccessible::Role >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QAccessibleInterface::setText(QAccessible::Text  t, const QString&  text)
{
    QScriptValue _q_function = __qtscript_self.property("setText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setText") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAccessibleInterface::setText() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, text));
        _q_function.setData(QScriptValue(false));
    }
}

QAccessible::State  QtScriptShell_QAccessibleInterface::state() const
{
    QScriptValue _q_function = __qtscript_self.property("state");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("state") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAccessibleInterface::state() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QAccessible::State _q_retval = qscriptvalue_cast<QAccessible::State >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QString  QtScriptShell_QAccessibleInterface::text(QAccessible::Text  t) const
{
    QScriptValue _q_function = __qtscript_self.property("text");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("text") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QAccessibleInterface::text() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QString _q_retval = qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, t)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QAccessibleInterface::virtual_hook(int  id, void*  data)
{
    QScriptValue _q_function = __qtscript_self.property("virtual_hook");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("virtual_hook") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QAccessibleInterface::virtual_hook(id, data);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, id)
            << qScriptValueFromValue(_q_engine, data));
        _q_function.setData(QScriptValue(false));
    }
}

QWindow*  QtScriptShell_QAccessibleInterface::window() const
{
    QScriptValue _q_function = __qtscript_self.property("window");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("window") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QAccessibleInterface::window();
    } else {
        _q_function.setData(QScriptValue(true));
        QWindow* _q_retval = qscriptvalue_cast<QWindow* >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

