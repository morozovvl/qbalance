#include "qtscriptshell_QCommonStyle.h"

#include <QtScript/QScriptEngine>
#include <QIconEngine>
#include <QVariant>
#include <qapplication.h>
#include <qbytearray.h>
#include <qcommonstyle.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QStyle::ComplexControl)
Q_DECLARE_METATYPE(QStyleOptionComplex*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QStyle::ControlElement)
Q_DECLARE_METATYPE(QStyleOption*)
Q_DECLARE_METATYPE(QPalette::ColorRole)
Q_DECLARE_METATYPE(QStyle::PrimitiveElement)
Q_DECLARE_METATYPE(QIcon::Mode)
Q_DECLARE_METATYPE(QStyle::SubControl)
Q_DECLARE_METATYPE(QSizePolicy::ControlType)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(QStyle::PixelMetric)
Q_DECLARE_METATYPE(QApplication*)
Q_DECLARE_METATYPE(QStyle::ContentsType)
Q_DECLARE_METATYPE(QStyle::StandardPixmap)
Q_DECLARE_METATYPE(QStyle::StyleHint)
Q_DECLARE_METATYPE(QStyleHintReturn*)
Q_DECLARE_METATYPE(QStyle::SubElement)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QCommonStyle::QtScriptShell_QCommonStyle()
    : QCommonStyle() {}

QtScriptShell_QCommonStyle::~QtScriptShell_QCommonStyle() {}

void QtScriptShell_QCommonStyle::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QCommonStyle::childEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QCommonStyle::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QCommonStyle::customEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QCommonStyle::drawComplexControl(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, QPainter*  p, const QWidget*  w) const
{
    QScriptValue _q_function = __qtscript_self.property("drawComplexControl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawComplexControl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QCommonStyle::drawComplexControl(cc, opt, p, w);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cc)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOptionComplex *>(opt))
            << qScriptValueFromValue(_q_engine, p)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(w)));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QCommonStyle::drawControl(QStyle::ControlElement  element, const QStyleOption*  opt, QPainter*  p, const QWidget*  w) const
{
    QScriptValue _q_function = __qtscript_self.property("drawControl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawControl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QCommonStyle::drawControl(element, opt, p, w);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, element)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, p)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(w)));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QCommonStyle::drawItemPixmap(QPainter*  painter, const QRect&  rect, int  alignment, const QPixmap&  pixmap) const
{
    QScriptValue _q_function = __qtscript_self.property("drawItemPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawItemPixmap") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QCommonStyle::drawItemPixmap(painter, rect, alignment, pixmap);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, alignment)
            << qScriptValueFromValue(_q_engine, pixmap));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QCommonStyle::drawItemText(QPainter*  painter, const QRect&  rect, int  flags, const QPalette&  pal, bool  enabled, const QString&  text, QPalette::ColorRole  textRole) const
{
    QScriptValue _q_function = __qtscript_self.property("drawItemText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawItemText") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QCommonStyle::drawItemText(painter, rect, flags, pal, enabled, text, textRole);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, flags)
            << qScriptValueFromValue(_q_engine, pal)
            << qScriptValueFromValue(_q_engine, enabled)
            << qScriptValueFromValue(_q_engine, text)
            << qScriptValueFromValue(_q_engine, textRole));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QCommonStyle::drawPrimitive(QStyle::PrimitiveElement  pe, const QStyleOption*  opt, QPainter*  p, const QWidget*  w) const
{
    QScriptValue _q_function = __qtscript_self.property("drawPrimitive");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawPrimitive") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QCommonStyle::drawPrimitive(pe, opt, p, w);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, pe)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, p)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(w)));
        _q_function.setData(QScriptValue(false));
    }
}

bool  QtScriptShell_QCommonStyle::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QCommonStyle::event(arg__1);
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

bool  QtScriptShell_QCommonStyle::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QCommonStyle::eventFilter(arg__1, arg__2);
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

QPixmap  QtScriptShell_QCommonStyle::generatedIconPixmap(QIcon::Mode  iconMode, const QPixmap&  pixmap, const QStyleOption*  opt) const
{
    QScriptValue _q_function = __qtscript_self.property("generatedIconPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("generatedIconPixmap") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QCommonStyle::generatedIconPixmap(iconMode, pixmap, opt);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QPixmap _q_retval = qscriptvalue_cast<QPixmap >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, iconMode)
            << qScriptValueFromValue(_q_engine, pixmap)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(opt))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QStyle::SubControl  QtScriptShell_QCommonStyle::hitTestComplexControl(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, const QPoint&  pt, const QWidget*  w) const
{
    QScriptValue _q_function = __qtscript_self.property("hitTestComplexControl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hitTestComplexControl") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QCommonStyle::hitTestComplexControl(cc, opt, pt, w);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QStyle::SubControl _q_retval = qscriptvalue_cast<QStyle::SubControl >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cc)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOptionComplex *>(opt))
            << qScriptValueFromValue(_q_engine, pt)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(w))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QRect  QtScriptShell_QCommonStyle::itemPixmapRect(const QRect&  r, int  flags, const QPixmap&  pixmap) const
{
    QScriptValue _q_function = __qtscript_self.property("itemPixmapRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemPixmapRect") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QCommonStyle::itemPixmapRect(r, flags, pixmap);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QRect _q_retval = qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, r)
            << qScriptValueFromValue(_q_engine, flags)
            << qScriptValueFromValue(_q_engine, pixmap)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QCommonStyle::layoutSpacing(QSizePolicy::ControlType  control1, QSizePolicy::ControlType  control2, Qt::Orientation  orientation, const QStyleOption*  option, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("layoutSpacing");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("layoutSpacing") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QCommonStyle::layoutSpacing(control1, control2, orientation, option, widget);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, control1)
            << qScriptValueFromValue(_q_engine, control2)
            << qScriptValueFromValue(_q_engine, orientation)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(option))
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QCommonStyle::pixelMetric(QStyle::PixelMetric  m, const QStyleOption*  opt, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("pixelMetric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("pixelMetric") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QCommonStyle::pixelMetric(m, opt, widget);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, m)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QCommonStyle::polish(QApplication*  app)
{
    QScriptValue _q_function = __qtscript_self.property("polish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("polish") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QCommonStyle::polish(app);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, app));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QCommonStyle::polish(QPalette&  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("polish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("polish") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QCommonStyle::polish(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QCommonStyle::polish(QWidget*  widget)
{
    QScriptValue _q_function = __qtscript_self.property("polish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("polish") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QCommonStyle::polish(widget);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, widget));
        _q_function.setData(QScriptValue(false));
    }
}

QSize  QtScriptShell_QCommonStyle::sizeFromContents(QStyle::ContentsType  ct, const QStyleOption*  opt, const QSize&  contentsSize, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeFromContents");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeFromContents") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QCommonStyle::sizeFromContents(ct, opt, contentsSize, widget);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QSize _q_retval = qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ct)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, contentsSize)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QIcon  QtScriptShell_QCommonStyle::standardIcon(QStyle::StandardPixmap  standardIcon, const QStyleOption*  opt, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("standardIcon");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("standardIcon") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QCommonStyle::standardIcon(standardIcon, opt, widget);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QIcon _q_retval = qscriptvalue_cast<QIcon >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, standardIcon)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QPalette  QtScriptShell_QCommonStyle::standardPalette() const
{
    QScriptValue _q_function = __qtscript_self.property("standardPalette");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("standardPalette") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QCommonStyle::standardPalette();
    } else {
        _q_function.setData(QScriptValue(true));
        QPalette _q_retval = qscriptvalue_cast<QPalette >(_q_function.call(__qtscript_self));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QPixmap  QtScriptShell_QCommonStyle::standardPixmap(QStyle::StandardPixmap  standardPixmap, const QStyleOption*  opt, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("standardPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("standardPixmap") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        qFatal("QCommonStyle::standardPixmap() is abstract!");
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QPixmap _q_retval = qscriptvalue_cast<QPixmap >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, standardPixmap)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

int  QtScriptShell_QCommonStyle::styleHint(QStyle::StyleHint  sh, const QStyleOption*  opt, const QWidget*  w, QStyleHintReturn*  shret) const
{
    QScriptValue _q_function = __qtscript_self.property("styleHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("styleHint") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QCommonStyle::styleHint(sh, opt, w, shret);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        int _q_retval = qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, sh)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(w))
            << qScriptValueFromValue(_q_engine, shret)));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QRect  QtScriptShell_QCommonStyle::subControlRect(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, QStyle::SubControl  sc, const QWidget*  w) const
{
    QScriptValue _q_function = __qtscript_self.property("subControlRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("subControlRect") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QCommonStyle::subControlRect(cc, opt, sc, w);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QRect _q_retval = qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cc)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOptionComplex *>(opt))
            << qScriptValueFromValue(_q_engine, sc)
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(w))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

QRect  QtScriptShell_QCommonStyle::subElementRect(QStyle::SubElement  r, const QStyleOption*  opt, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("subElementRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("subElementRect") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        return QCommonStyle::subElementRect(r, opt, widget);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        QRect _q_retval = qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, r)
            << qScriptValueFromValue(_q_engine, const_cast<QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, const_cast<QWidget *>(widget))));
        _q_function.setData(QScriptValue(false));
        return _q_retval;
    }
}

void QtScriptShell_QCommonStyle::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QCommonStyle::timerEvent(arg__1);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QCommonStyle::unpolish(QApplication*  application)
{
    QScriptValue _q_function = __qtscript_self.property("unpolish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unpolish") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QCommonStyle::unpolish(application);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, application));
        _q_function.setData(QScriptValue(false));
    }
}

void QtScriptShell_QCommonStyle::unpolish(QWidget*  widget)
{
    QScriptValue _q_function = __qtscript_self.property("unpolish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unpolish") & QScriptValue::QObjectMember)
        || (_q_function.data().toBool() == true)) {
        QCommonStyle::unpolish(widget);
    } else {
        _q_function.setData(QScriptValue(true));
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, widget));
        _q_function.setData(QScriptValue(false));
    }
}

