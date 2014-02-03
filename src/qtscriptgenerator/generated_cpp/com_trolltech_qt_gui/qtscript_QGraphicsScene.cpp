#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgraphicsscene.h>
#include <QVarLengthArray>
#include <QVariant>
#include <qbrush.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicsitem.h>
#include <qgraphicsproxywidget.h>
#include <qgraphicsscene.h>
#include <qgraphicssceneevent.h>
#include <qgraphicsview.h>
#include <qgraphicswidget.h>
#include <qline.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpalette.h>
#include <qpen.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qtransform.h>
#include <qwidget.h>

#include "qtscriptshell_QGraphicsScene.h"

static const char * const qtscript_QGraphicsScene_function_names[] = {
    "QGraphicsScene"
    // static
    // prototype
    , "activePanel"
    , "activeWindow"
    , "addEllipse"
    , "addItem"
    , "addLine"
    , "addPath"
    , "addPixmap"
    , "addPolygon"
    , "addRect"
    , "addSimpleText"
    , "addText"
    , "addWidget"
    , "clearFocus"
    , "collidingItems"
    , "contextMenuEvent"
    , "createItemGroup"
    , "destroyItemGroup"
    , "dragEnterEvent"
    , "dragLeaveEvent"
    , "dragMoveEvent"
    , "drawBackground"
    , "drawForeground"
    , "drawItems"
    , "dropEvent"
    , "focusInEvent"
    , "focusItem"
    , "focusOutEvent"
    , "hasFocus"
    , "height"
    , "helpEvent"
    , "inputMethodEvent"
    , "inputMethodQuery"
    , "invalidate"
    , "isActive"
    , "itemAt"
    , "items"
    , "itemsBoundingRect"
    , "keyPressEvent"
    , "keyReleaseEvent"
    , "mouseDoubleClickEvent"
    , "mouseGrabberItem"
    , "mouseMoveEvent"
    , "mousePressEvent"
    , "mouseReleaseEvent"
    , "removeItem"
    , "render"
    , "selectedItems"
    , "selectionArea"
    , "sendEvent"
    , "setActivePanel"
    , "setActiveWindow"
    , "setFocus"
    , "setFocusItem"
    , "setSceneRect"
    , "setSelectionArea"
    , "setStyle"
    , "style"
    , "update"
    , "views"
    , "wheelEvent"
    , "width"
    , "toString"
};

static const char * const qtscript_QGraphicsScene_function_signatures[] = {
    "QObject parent\nQRectF sceneRect, QObject parent\nqreal x, qreal y, qreal width, qreal height, QObject parent"
    // static
    // prototype
    , ""
    , ""
    , "QRectF rect, QPen pen, QBrush brush\nqreal x, qreal y, qreal w, qreal h, QPen pen, QBrush brush"
    , "QGraphicsItem item"
    , "QLineF line, QPen pen\nqreal x1, qreal y1, qreal x2, qreal y2, QPen pen"
    , "QPainterPath path, QPen pen, QBrush brush"
    , "QPixmap pixmap"
    , "QPolygonF polygon, QPen pen, QBrush brush"
    , "QRectF rect, QPen pen, QBrush brush\nqreal x, qreal y, qreal w, qreal h, QPen pen, QBrush brush"
    , "String text, QFont font"
    , "String text, QFont font"
    , "QWidget widget, WindowFlags wFlags"
    , ""
    , "QGraphicsItem item, ItemSelectionMode mode"
    , "QGraphicsSceneContextMenuEvent event"
    , "List items"
    , "QGraphicsItemGroup group"
    , "QGraphicsSceneDragDropEvent event"
    , "QGraphicsSceneDragDropEvent event"
    , "QGraphicsSceneDragDropEvent event"
    , "QPainter painter, QRectF rect"
    , "QPainter painter, QRectF rect"
    , "QPainter painter, int numItems, QGraphicsItem items, QStyleOptionGraphicsItem options, QWidget widget"
    , "QGraphicsSceneDragDropEvent event"
    , "QFocusEvent event"
    , ""
    , "QFocusEvent event"
    , ""
    , ""
    , "QGraphicsSceneHelpEvent event"
    , "QInputMethodEvent event"
    , "InputMethodQuery query"
    , "qreal x, qreal y, qreal w, qreal h, SceneLayers layers"
    , ""
    , "QPointF pos, QTransform deviceTransform\nqreal x, qreal y, QTransform deviceTransform"
    , "SortOrder order\nQPainterPath path, ItemSelectionMode mode, SortOrder order, QTransform deviceTransform\nQPointF pos, ItemSelectionMode mode, SortOrder order, QTransform deviceTransform\nQPolygonF polygon, ItemSelectionMode mode, SortOrder order, QTransform deviceTransform\nQRectF rect, ItemSelectionMode mode, SortOrder order, QTransform deviceTransform\nqreal x, qreal y, qreal w, qreal h, ItemSelectionMode mode, SortOrder order, QTransform deviceTransform"
    , ""
    , "QKeyEvent event"
    , "QKeyEvent event"
    , "QGraphicsSceneMouseEvent event"
    , ""
    , "QGraphicsSceneMouseEvent event"
    , "QGraphicsSceneMouseEvent event"
    , "QGraphicsSceneMouseEvent event"
    , "QGraphicsItem item"
    , "QPainter painter, QRectF target, QRectF source, AspectRatioMode aspectRatioMode"
    , ""
    , ""
    , "QGraphicsItem item, QEvent event"
    , "QGraphicsItem item"
    , "QGraphicsWidget widget"
    , "FocusReason focusReason"
    , "QGraphicsItem item, FocusReason focusReason"
    , "qreal x, qreal y, qreal w, qreal h"
    , "QPainterPath path, ItemSelectionMode mode, QTransform deviceTransform\nQPainterPath path, QTransform deviceTransform"
    , "QStyle style"
    , ""
    , "qreal x, qreal y, qreal w, qreal h"
    , ""
    , "QGraphicsSceneWheelEvent event"
    , ""
""
};

static const int qtscript_QGraphicsScene_function_lengths[] = {
    5
    // static
    // prototype
    , 0
    , 0
    , 6
    , 1
    , 5
    , 3
    , 1
    , 3
    , 6
    , 2
    , 2
    , 2
    , 0
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
    , 2
    , 5
    , 1
    , 1
    , 0
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
    , 5
    , 0
    , 3
    , 7
    , 0
    , 1
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 4
    , 0
    , 0
    , 2
    , 1
    , 1
    , 1
    , 2
    , 4
    , 3
    , 1
    , 0
    , 4
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QGraphicsScene_prototype_call(QScriptContext *, QScriptEngine *);

class qtscript_QGraphicsScene : public QGraphicsScene
{
    friend QScriptValue qtscript_QGraphicsScene_contextMenuEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_dragEnterEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_dragLeaveEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_dragMoveEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_drawBackground(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_drawForeground(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_drawItems(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_dropEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_focusInEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_focusOutEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_helpEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_inputMethodEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_keyPressEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_keyReleaseEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_mouseDoubleClickEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_mouseMoveEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_mousePressEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_mouseReleaseEvent(QScriptContext *, QScriptEngine *);
    friend QScriptValue qtscript_QGraphicsScene_wheelEvent(QScriptContext *, QScriptEngine *);

    friend QScriptValue qtscript_QGraphicsScene_prototype_call(QScriptContext *, QScriptEngine *);

};

static QScriptValue qtscript_QGraphicsScene_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsScene::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsScene*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsScene*)
Q_DECLARE_METATYPE(QGraphicsScene::ItemIndexMethod)
Q_DECLARE_METATYPE(QGraphicsScene::SceneLayer)
Q_DECLARE_METATYPE(QFlags<QGraphicsScene::SceneLayer>)
Q_DECLARE_METATYPE(QGraphicsWidget*)
Q_DECLARE_METATYPE(QGraphicsEllipseItem*)
Q_DECLARE_METATYPE(QGraphicsLineItem*)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(QGraphicsPathItem*)
Q_DECLARE_METATYPE(QGraphicsPixmapItem*)
Q_DECLARE_METATYPE(QGraphicsPolygonItem*)
Q_DECLARE_METATYPE(QGraphicsRectItem*)
Q_DECLARE_METATYPE(QGraphicsSimpleTextItem*)
Q_DECLARE_METATYPE(QGraphicsTextItem*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)
Q_DECLARE_METATYPE(QGraphicsProxyWidget*)
Q_DECLARE_METATYPE(Qt::ItemSelectionMode)
Q_DECLARE_METATYPE(QList<QGraphicsItem*>)
Q_DECLARE_METATYPE(QGraphicsSceneContextMenuEvent*)
Q_DECLARE_METATYPE(QGraphicsItemGroup*)
Q_DECLARE_METATYPE(QGraphicsSceneDragDropEvent*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QGraphicsItem**)
Q_DECLARE_METATYPE(QStyleOptionGraphicsItem*)
Q_DECLARE_METATYPE(QFocusEvent*)
Q_DECLARE_METATYPE(QGraphicsSceneHelpEvent*)
Q_DECLARE_METATYPE(QInputMethodEvent*)
Q_DECLARE_METATYPE(Qt::InputMethodQuery)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QKeyEvent*)
Q_DECLARE_METATYPE(QGraphicsSceneMouseEvent*)
Q_DECLARE_METATYPE(Qt::AspectRatioMode)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(Qt::FocusReason)
Q_DECLARE_METATYPE(QStyle*)
Q_DECLARE_METATYPE(QGraphicsView*)
Q_DECLARE_METATYPE(QList<QGraphicsView*>)
Q_DECLARE_METATYPE(QGraphicsSceneWheelEvent*)

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

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QGraphicsScene::ItemIndexMethod
//

static const QGraphicsScene::ItemIndexMethod qtscript_QGraphicsScene_ItemIndexMethod_values[] = {
    QGraphicsScene::NoIndex
    , QGraphicsScene::BspTreeIndex
};

static const char * const qtscript_QGraphicsScene_ItemIndexMethod_keys[] = {
    "NoIndex"
    , "BspTreeIndex"
};

static QString qtscript_QGraphicsScene_ItemIndexMethod_toStringHelper(QGraphicsScene::ItemIndexMethod value)
{
    if ((value >= QGraphicsScene::NoIndex) && (value <= QGraphicsScene::BspTreeIndex))
        return qtscript_QGraphicsScene_ItemIndexMethod_keys[static_cast<int>(value)-static_cast<int>(QGraphicsScene::NoIndex)];
    return QString();
}

static QScriptValue qtscript_QGraphicsScene_ItemIndexMethod_toScriptValue(QScriptEngine *engine, const QGraphicsScene::ItemIndexMethod &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGraphicsScene"));
    return clazz.property(qtscript_QGraphicsScene_ItemIndexMethod_toStringHelper(value));
}

static void qtscript_QGraphicsScene_ItemIndexMethod_fromScriptValue(const QScriptValue &value, QGraphicsScene::ItemIndexMethod &out)
{
    out = qvariant_cast<QGraphicsScene::ItemIndexMethod>(value.toVariant());
}

static QScriptValue qtscript_construct_QGraphicsScene_ItemIndexMethod(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QGraphicsScene::NoIndex) && (arg <= QGraphicsScene::BspTreeIndex))
        return qScriptValueFromValue(engine,  static_cast<QGraphicsScene::ItemIndexMethod>(arg));
    return context->throwError(QString::fromLatin1("ItemIndexMethod(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGraphicsScene_ItemIndexMethod_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsScene::ItemIndexMethod value = qscriptvalue_cast<QGraphicsScene::ItemIndexMethod>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsScene_ItemIndexMethod_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsScene::ItemIndexMethod value = qscriptvalue_cast<QGraphicsScene::ItemIndexMethod>(context->thisObject());
    return QScriptValue(engine, qtscript_QGraphicsScene_ItemIndexMethod_toStringHelper(value));
}

static QScriptValue qtscript_create_QGraphicsScene_ItemIndexMethod_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGraphicsScene_ItemIndexMethod,
        qtscript_QGraphicsScene_ItemIndexMethod_valueOf, qtscript_QGraphicsScene_ItemIndexMethod_toString);
    qScriptRegisterMetaType<QGraphicsScene::ItemIndexMethod>(engine, qtscript_QGraphicsScene_ItemIndexMethod_toScriptValue,
        qtscript_QGraphicsScene_ItemIndexMethod_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGraphicsScene_ItemIndexMethod_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGraphicsScene_ItemIndexMethod_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGraphicsScene::SceneLayer
//

static const QGraphicsScene::SceneLayer qtscript_QGraphicsScene_SceneLayer_values[] = {
    QGraphicsScene::ItemLayer
    , QGraphicsScene::BackgroundLayer
    , QGraphicsScene::ForegroundLayer
    , QGraphicsScene::AllLayers
};

static const char * const qtscript_QGraphicsScene_SceneLayer_keys[] = {
    "ItemLayer"
    , "BackgroundLayer"
    , "ForegroundLayer"
    , "AllLayers"
};

static QString qtscript_QGraphicsScene_SceneLayer_toStringHelper(QGraphicsScene::SceneLayer value)
{
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QGraphicsScene_SceneLayer_values[i] == value)
            return QString::fromLatin1(qtscript_QGraphicsScene_SceneLayer_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QGraphicsScene_SceneLayer_toScriptValue(QScriptEngine *engine, const QGraphicsScene::SceneLayer &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGraphicsScene"));
    return clazz.property(qtscript_QGraphicsScene_SceneLayer_toStringHelper(value));
}

static void qtscript_QGraphicsScene_SceneLayer_fromScriptValue(const QScriptValue &value, QGraphicsScene::SceneLayer &out)
{
    out = qvariant_cast<QGraphicsScene::SceneLayer>(value.toVariant());
}

static QScriptValue qtscript_construct_QGraphicsScene_SceneLayer(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QGraphicsScene_SceneLayer_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QGraphicsScene::SceneLayer>(arg));
    }
    return context->throwError(QString::fromLatin1("SceneLayer(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGraphicsScene_SceneLayer_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsScene::SceneLayer value = qscriptvalue_cast<QGraphicsScene::SceneLayer>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsScene_SceneLayer_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsScene::SceneLayer value = qscriptvalue_cast<QGraphicsScene::SceneLayer>(context->thisObject());
    return QScriptValue(engine, qtscript_QGraphicsScene_SceneLayer_toStringHelper(value));
}

static QScriptValue qtscript_create_QGraphicsScene_SceneLayer_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGraphicsScene_SceneLayer,
        qtscript_QGraphicsScene_SceneLayer_valueOf, qtscript_QGraphicsScene_SceneLayer_toString);
    qScriptRegisterMetaType<QGraphicsScene::SceneLayer>(engine, qtscript_QGraphicsScene_SceneLayer_toScriptValue,
        qtscript_QGraphicsScene_SceneLayer_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGraphicsScene_SceneLayer_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGraphicsScene_SceneLayer_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGraphicsScene::SceneLayers
//

static QScriptValue qtscript_QGraphicsScene_SceneLayers_toScriptValue(QScriptEngine *engine, const QGraphicsScene::SceneLayers &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QGraphicsScene_SceneLayers_fromScriptValue(const QScriptValue &value, QGraphicsScene::SceneLayers &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QGraphicsScene::SceneLayers>())
        out = qvariant_cast<QGraphicsScene::SceneLayers>(var);
    else if (var.userType() == qMetaTypeId<QGraphicsScene::SceneLayer>())
        out = qvariant_cast<QGraphicsScene::SceneLayer>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QGraphicsScene_SceneLayers(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsScene::SceneLayers result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QGraphicsScene::SceneLayers>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QGraphicsScene::SceneLayer>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("SceneLayers(): argument %0 is not of type SceneLayer").arg(i));
            }
            result |= qvariant_cast<QGraphicsScene::SceneLayer>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QGraphicsScene_SceneLayers_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsScene::SceneLayers value = qscriptvalue_cast<QGraphicsScene::SceneLayers>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsScene_SceneLayers_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsScene::SceneLayers value = qscriptvalue_cast<QGraphicsScene::SceneLayers>(context->thisObject());
    QString result;
    for (int i = 0; i < 4; ++i) {
        if ((value & qtscript_QGraphicsScene_SceneLayer_values[i]) == qtscript_QGraphicsScene_SceneLayer_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QGraphicsScene_SceneLayer_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QGraphicsScene_SceneLayers_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QGraphicsScene::SceneLayers>() == otherObj.value<QGraphicsScene::SceneLayers>())));
}

static QScriptValue qtscript_create_QGraphicsScene_SceneLayers_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QGraphicsScene_SceneLayers, qtscript_QGraphicsScene_SceneLayers_valueOf,
        qtscript_QGraphicsScene_SceneLayers_toString, qtscript_QGraphicsScene_SceneLayers_equals);
    qScriptRegisterMetaType<QGraphicsScene::SceneLayers>(engine, qtscript_QGraphicsScene_SceneLayers_toScriptValue,
        qtscript_QGraphicsScene_SceneLayers_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QGraphicsScene
//

static QScriptValue qtscript_QGraphicsScene_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 61;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    qtscript_QGraphicsScene* _q_self = reinterpret_cast<qtscript_QGraphicsScene*>(qscriptvalue_cast<QGraphicsScene*>(context->thisObject()));
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsScene.%0(): this object is not a QGraphicsScene")
            .arg(qtscript_QGraphicsScene_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QGraphicsItem* _q_result = _q_self->activePanel();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QGraphicsWidget* _q_result = _q_self->activeWindow();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QGraphicsEllipseItem* _q_result = _q_self->addEllipse(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QPen _q_arg1 = qscriptvalue_cast<QPen>(context->argument(1));
        QGraphicsEllipseItem* _q_result = _q_self->addEllipse(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QPen _q_arg1 = qscriptvalue_cast<QPen>(context->argument(1));
        QBrush _q_arg2 = qscriptvalue_cast<QBrush>(context->argument(2));
        QGraphicsEllipseItem* _q_result = _q_self->addEllipse(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QGraphicsEllipseItem* _q_result = _q_self->addEllipse(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QPen _q_arg4 = qscriptvalue_cast<QPen>(context->argument(4));
        QGraphicsEllipseItem* _q_result = _q_self->addEllipse(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QPen _q_arg4 = qscriptvalue_cast<QPen>(context->argument(4));
        QBrush _q_arg5 = qscriptvalue_cast<QBrush>(context->argument(5));
        QGraphicsEllipseItem* _q_result = _q_self->addEllipse(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        _q_self->addItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QLineF _q_arg0 = qscriptvalue_cast<QLineF>(context->argument(0));
        QGraphicsLineItem* _q_result = _q_self->addLine(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QLineF _q_arg0 = qscriptvalue_cast<QLineF>(context->argument(0));
        QPen _q_arg1 = qscriptvalue_cast<QPen>(context->argument(1));
        QGraphicsLineItem* _q_result = _q_self->addLine(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QGraphicsLineItem* _q_result = _q_self->addLine(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QPen _q_arg4 = qscriptvalue_cast<QPen>(context->argument(4));
        QGraphicsLineItem* _q_result = _q_self->addLine(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QGraphicsPathItem* _q_result = _q_self->addPath(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPen _q_arg1 = qscriptvalue_cast<QPen>(context->argument(1));
        QGraphicsPathItem* _q_result = _q_self->addPath(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPen _q_arg1 = qscriptvalue_cast<QPen>(context->argument(1));
        QBrush _q_arg2 = qscriptvalue_cast<QBrush>(context->argument(2));
        QGraphicsPathItem* _q_result = _q_self->addPath(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
        QGraphicsPixmapItem* _q_result = _q_self->addPixmap(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
        QGraphicsPolygonItem* _q_result = _q_self->addPolygon(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
        QPen _q_arg1 = qscriptvalue_cast<QPen>(context->argument(1));
        QGraphicsPolygonItem* _q_result = _q_self->addPolygon(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
        QPen _q_arg1 = qscriptvalue_cast<QPen>(context->argument(1));
        QBrush _q_arg2 = qscriptvalue_cast<QBrush>(context->argument(2));
        QGraphicsPolygonItem* _q_result = _q_self->addPolygon(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QGraphicsRectItem* _q_result = _q_self->addRect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QPen _q_arg1 = qscriptvalue_cast<QPen>(context->argument(1));
        QGraphicsRectItem* _q_result = _q_self->addRect(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QPen _q_arg1 = qscriptvalue_cast<QPen>(context->argument(1));
        QBrush _q_arg2 = qscriptvalue_cast<QBrush>(context->argument(2));
        QGraphicsRectItem* _q_result = _q_self->addRect(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QGraphicsRectItem* _q_result = _q_self->addRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QPen _q_arg4 = qscriptvalue_cast<QPen>(context->argument(4));
        QGraphicsRectItem* _q_result = _q_self->addRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QPen _q_arg4 = qscriptvalue_cast<QPen>(context->argument(4));
        QBrush _q_arg5 = qscriptvalue_cast<QBrush>(context->argument(5));
        QGraphicsRectItem* _q_result = _q_self->addRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QGraphicsSimpleTextItem* _q_result = _q_self->addSimpleText(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QFont _q_arg1 = qscriptvalue_cast<QFont>(context->argument(1));
        QGraphicsSimpleTextItem* _q_result = _q_self->addSimpleText(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QGraphicsTextItem* _q_result = _q_self->addText(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QFont _q_arg1 = qscriptvalue_cast<QFont>(context->argument(1));
        QGraphicsTextItem* _q_result = _q_self->addText(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {

          QScriptValue _q_arg0_orig = context->argument(0);
          QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(_q_arg0_orig);
          if (_q_arg0 != 0)
              context->engine()->newQObject(_q_arg0_orig, _q_arg0, QScriptEngine::QtOwnership);
                  QGraphicsProxyWidget* _q_result = _q_self->addWidget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {

          QScriptValue _q_arg0_orig = context->argument(0);
          QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(_q_arg0_orig);
          if (_q_arg0 != 0)
              context->engine()->newQObject(_q_arg0_orig, _q_arg0, QScriptEngine::QtOwnership);
                  QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
        QGraphicsProxyWidget* _q_result = _q_self->addWidget(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        _q_self->clearFocus();
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        QList<QGraphicsItem*> _q_result = _q_self->collidingItems(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
        QList<QGraphicsItem*> _q_result = _q_self->collidingItems(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QGraphicsSceneContextMenuEvent* _q_arg0 = qscriptvalue_cast<QGraphicsSceneContextMenuEvent*>(context->argument(0));
        _q_self->contextMenuEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QList<QGraphicsItem*> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QGraphicsItemGroup* _q_result = _q_self->createItemGroup(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QGraphicsItemGroup* _q_arg0 = qscriptvalue_cast<QGraphicsItemGroup*>(context->argument(0));
        _q_self->destroyItemGroup(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QGraphicsSceneDragDropEvent* _q_arg0 = qscriptvalue_cast<QGraphicsSceneDragDropEvent*>(context->argument(0));
        _q_self->dragEnterEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QGraphicsSceneDragDropEvent* _q_arg0 = qscriptvalue_cast<QGraphicsSceneDragDropEvent*>(context->argument(0));
        _q_self->dragLeaveEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QGraphicsSceneDragDropEvent* _q_arg0 = qscriptvalue_cast<QGraphicsSceneDragDropEvent*>(context->argument(0));
        _q_self->dragMoveEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 2) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRectF _q_arg1 = qscriptvalue_cast<QRectF>(context->argument(1));
        _q_self->drawBackground(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 2) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRectF _q_arg1 = qscriptvalue_cast<QRectF>(context->argument(1));
        _q_self->drawForeground(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 4) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QGraphicsItem** _q_arg2 = qscriptvalue_cast<QGraphicsItem**>(context->argument(2));
        QStyleOptionGraphicsItem* _q_arg3 = qscriptvalue_cast<QStyleOptionGraphicsItem*>(context->argument(3));
        _q_self->drawItems(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QGraphicsItem** _q_arg2 = qscriptvalue_cast<QGraphicsItem**>(context->argument(2));
        QStyleOptionGraphicsItem* _q_arg3 = qscriptvalue_cast<QStyleOptionGraphicsItem*>(context->argument(3));
        QWidget* _q_arg4 = qscriptvalue_cast<QWidget*>(context->argument(4));
        _q_self->drawItems(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QGraphicsSceneDragDropEvent* _q_arg0 = qscriptvalue_cast<QGraphicsSceneDragDropEvent*>(context->argument(0));
        _q_self->dropEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QFocusEvent* _q_arg0 = qscriptvalue_cast<QFocusEvent*>(context->argument(0));
        _q_self->focusInEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        QGraphicsItem* _q_result = _q_self->focusItem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QFocusEvent* _q_arg0 = qscriptvalue_cast<QFocusEvent*>(context->argument(0));
        _q_self->focusOutEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasFocus();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->height();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        QGraphicsSceneHelpEvent* _q_arg0 = qscriptvalue_cast<QGraphicsSceneHelpEvent*>(context->argument(0));
        _q_self->helpEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QInputMethodEvent* _q_arg0 = qscriptvalue_cast<QInputMethodEvent*>(context->argument(0));
        _q_self->inputMethodEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        Qt::InputMethodQuery _q_arg0 = qscriptvalue_cast<Qt::InputMethodQuery>(context->argument(0));
        QVariant _q_result = _q_self->inputMethodQuery(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->invalidate(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QFlags<QGraphicsScene::SceneLayer> _q_arg4 = qscriptvalue_cast<QFlags<QGraphicsScene::SceneLayer> >(context->argument(4));
        _q_self->invalidate(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isActive();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 2) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        QTransform _q_arg1 = qscriptvalue_cast<QTransform>(context->argument(1));
        QGraphicsItem* _q_result = _q_self->itemAt(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QTransform _q_arg2 = qscriptvalue_cast<QTransform>(context->argument(2));
        QGraphicsItem* _q_result = _q_self->itemAt(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 0) {
        QList<QGraphicsItem*> _q_result = _q_self->items();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Qt::SortOrder>() == context->argument(0).toVariant().userType())) {
            Qt::SortOrder _q_arg0 = qscriptvalue_cast<Qt::SortOrder>(context->argument(0));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0, _q_arg1);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0, _q_arg1);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0, _q_arg1);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0, _q_arg1);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<Qt::SortOrder>() == context->argument(2).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            Qt::SortOrder _q_arg2 = qscriptvalue_cast<Qt::SortOrder>(context->argument(2));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<Qt::SortOrder>() == context->argument(2).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            Qt::SortOrder _q_arg2 = qscriptvalue_cast<Qt::SortOrder>(context->argument(2));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<Qt::SortOrder>() == context->argument(2).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            Qt::SortOrder _q_arg2 = qscriptvalue_cast<Qt::SortOrder>(context->argument(2));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<Qt::SortOrder>() == context->argument(2).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            Qt::SortOrder _q_arg2 = qscriptvalue_cast<Qt::SortOrder>(context->argument(2));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 4) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<Qt::SortOrder>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QTransform>() == context->argument(3).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            Qt::SortOrder _q_arg2 = qscriptvalue_cast<Qt::SortOrder>(context->argument(2));
            QTransform _q_arg3 = qscriptvalue_cast<QTransform>(context->argument(3));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<Qt::SortOrder>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QTransform>() == context->argument(3).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            Qt::SortOrder _q_arg2 = qscriptvalue_cast<Qt::SortOrder>(context->argument(2));
            QTransform _q_arg3 = qscriptvalue_cast<QTransform>(context->argument(3));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<Qt::SortOrder>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QTransform>() == context->argument(3).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            Qt::SortOrder _q_arg2 = qscriptvalue_cast<Qt::SortOrder>(context->argument(2));
            QTransform _q_arg3 = qscriptvalue_cast<QTransform>(context->argument(3));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<Qt::SortOrder>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QTransform>() == context->argument(3).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            Qt::SortOrder _q_arg2 = qscriptvalue_cast<Qt::SortOrder>(context->argument(2));
            QTransform _q_arg3 = qscriptvalue_cast<QTransform>(context->argument(3));
            QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        Qt::ItemSelectionMode _q_arg4 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(4));
        Qt::SortOrder _q_arg5 = qscriptvalue_cast<Qt::SortOrder>(context->argument(5));
        QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 7) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        Qt::ItemSelectionMode _q_arg4 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(4));
        Qt::SortOrder _q_arg5 = qscriptvalue_cast<Qt::SortOrder>(context->argument(5));
        QTransform _q_arg6 = qscriptvalue_cast<QTransform>(context->argument(6));
        QList<QGraphicsItem*> _q_result = _q_self->items(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->itemsBoundingRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        QKeyEvent* _q_arg0 = qscriptvalue_cast<QKeyEvent*>(context->argument(0));
        _q_self->keyPressEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QKeyEvent* _q_arg0 = qscriptvalue_cast<QKeyEvent*>(context->argument(0));
        _q_self->keyReleaseEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        QGraphicsSceneMouseEvent* _q_arg0 = qscriptvalue_cast<QGraphicsSceneMouseEvent*>(context->argument(0));
        _q_self->mouseDoubleClickEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 0) {
        QGraphicsItem* _q_result = _q_self->mouseGrabberItem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 41:
    if (context->argumentCount() == 1) {
        QGraphicsSceneMouseEvent* _q_arg0 = qscriptvalue_cast<QGraphicsSceneMouseEvent*>(context->argument(0));
        _q_self->mouseMoveEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 1) {
        QGraphicsSceneMouseEvent* _q_arg0 = qscriptvalue_cast<QGraphicsSceneMouseEvent*>(context->argument(0));
        _q_self->mousePressEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 43:
    if (context->argumentCount() == 1) {
        QGraphicsSceneMouseEvent* _q_arg0 = qscriptvalue_cast<QGraphicsSceneMouseEvent*>(context->argument(0));
        _q_self->mouseReleaseEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 44:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        _q_self->removeItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        _q_self->render(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRectF _q_arg1 = qscriptvalue_cast<QRectF>(context->argument(1));
        _q_self->render(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRectF _q_arg1 = qscriptvalue_cast<QRectF>(context->argument(1));
        QRectF _q_arg2 = qscriptvalue_cast<QRectF>(context->argument(2));
        _q_self->render(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRectF _q_arg1 = qscriptvalue_cast<QRectF>(context->argument(1));
        QRectF _q_arg2 = qscriptvalue_cast<QRectF>(context->argument(2));
        Qt::AspectRatioMode _q_arg3 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(3));
        _q_self->render(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 46:
    if (context->argumentCount() == 0) {
        QList<QGraphicsItem*> _q_result = _q_self->selectedItems();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 47:
    if (context->argumentCount() == 0) {
        QPainterPath _q_result = _q_self->selectionArea();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 48:
    if (context->argumentCount() == 2) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        QEvent* _q_arg1 = qscriptvalue_cast<QEvent*>(context->argument(1));
        bool _q_result = _q_self->sendEvent(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 49:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        _q_self->setActivePanel(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 50:
    if (context->argumentCount() == 1) {
        QGraphicsWidget* _q_arg0 = qscriptvalue_cast<QGraphicsWidget*>(context->argument(0));
        _q_self->setActiveWindow(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 51:
    if (context->argumentCount() == 0) {
        _q_self->setFocus();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        Qt::FocusReason _q_arg0 = qscriptvalue_cast<Qt::FocusReason>(context->argument(0));
        _q_self->setFocus(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 52:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        _q_self->setFocusItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        Qt::FocusReason _q_arg1 = qscriptvalue_cast<Qt::FocusReason>(context->argument(1));
        _q_self->setFocusItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 53:
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->setSceneRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 54:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        _q_self->setSelectionArea(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            _q_self->setSelectionArea(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QTransform>() == context->argument(1).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            QTransform _q_arg1 = qscriptvalue_cast<QTransform>(context->argument(1));
            _q_self->setSelectionArea(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
        QTransform _q_arg2 = qscriptvalue_cast<QTransform>(context->argument(2));
        _q_self->setSelectionArea(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 55:
    if (context->argumentCount() == 1) {
        QStyle* _q_arg0 = qscriptvalue_cast<QStyle*>(context->argument(0));
        _q_self->setStyle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 56:
    if (context->argumentCount() == 0) {
        QStyle* _q_result = _q_self->style();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 57:
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->update(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 58:
    if (context->argumentCount() == 0) {
        QList<QGraphicsView*> _q_result = _q_self->views();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 59:
    if (context->argumentCount() == 1) {
        QGraphicsSceneWheelEvent* _q_arg0 = qscriptvalue_cast<QGraphicsSceneWheelEvent*>(context->argument(0));
        _q_self->wheelEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 60:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->width();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 61: {
    QString result = QString::fromLatin1("QGraphicsScene");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsScene_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsScene_function_names[_id+1],
        qtscript_QGraphicsScene_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsScene_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsScene(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsScene* _q_cpp_result = new QtScriptShell_QGraphicsScene();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsScene*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QGraphicsScene* _q_cpp_result = new QtScriptShell_QGraphicsScene(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsScene*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QtScriptShell_QGraphicsScene* _q_cpp_result = new QtScriptShell_QGraphicsScene(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsScene*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QGraphicsScene* _q_cpp_result = new QtScriptShell_QGraphicsScene(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsScene*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QtScriptShell_QGraphicsScene* _q_cpp_result = new QtScriptShell_QGraphicsScene(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsScene*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QObject* _q_arg4 = context->argument(4).toQObject();
        QtScriptShell_QGraphicsScene* _q_cpp_result = new QtScriptShell_QGraphicsScene(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsScene*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsScene_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsScene_function_names[_id],
        qtscript_QGraphicsScene_function_signatures[_id]);
}

static QScriptValue qtscript_QGraphicsScene_toScriptValue(QScriptEngine *engine, QGraphicsScene* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGraphicsScene_fromScriptValue(const QScriptValue &value, QGraphicsScene* &out)
{
    out = qobject_cast<QGraphicsScene*>(value.toQObject());
}

QScriptValue qtscript_create_QGraphicsScene_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsScene*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsScene*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 62; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsScene_prototype_call, qtscript_QGraphicsScene_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsScene_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGraphicsScene*>(engine, qtscript_QGraphicsScene_toScriptValue, 
        qtscript_QGraphicsScene_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsScene_static_call, proto, qtscript_QGraphicsScene_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ItemIndexMethod"),
        qtscript_create_QGraphicsScene_ItemIndexMethod_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SceneLayer"),
        qtscript_create_QGraphicsScene_SceneLayer_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SceneLayers"),
        qtscript_create_QGraphicsScene_SceneLayers_class(engine));
    return ctor;
}
