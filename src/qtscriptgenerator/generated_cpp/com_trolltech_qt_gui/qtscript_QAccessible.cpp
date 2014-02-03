#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qaccessible.h>
#include <QVariant>
#include <qaccessible.h>
#include <qobject.h>
#include <qpair.h>
#include <qtextcursor.h>

static const char * const qtscript_QAccessible_function_names[] = {
    "QAccessible"
    // static
    , "isActive"
    , "qAccessibleTextBoundaryHelper"
    , "queryAccessibleInterface"
    , "setRootObject"
    , "updateAccessibility"
    // prototype
    , "toString"
};

static const char * const qtscript_QAccessible_function_signatures[] = {
    ""
    // static
    , ""
    , "QTextCursor cursor, TextBoundaryType boundaryType"
    , "QObject arg__1"
    , "QObject object"
    , "QAccessibleEvent event"
    // prototype
""
};

static const int qtscript_QAccessible_function_lengths[] = {
    0
    // static
    , 0
    , 2
    , 1
    , 1
    , 1
    // prototype
    , 0
};

static QScriptValue qtscript_QAccessible_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAccessible::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QAccessible_metaObject()
{
    return &QAccessible::staticMetaObject;
}

Q_DECLARE_METATYPE(QAccessible*)
Q_DECLARE_METATYPE(QAccessible::Text)
Q_DECLARE_METATYPE(QAccessible::RelationFlag)
Q_DECLARE_METATYPE(QFlags<QAccessible::RelationFlag>)
Q_DECLARE_METATYPE(QAccessible::TextBoundaryType)
Q_DECLARE_METATYPE(QAccessible::InterfaceType)
Q_DECLARE_METATYPE(QAccessible::Event)
Q_DECLARE_METATYPE(QAccessible::Role)
Q_DECLARE_METATYPE(QTextCursor)
#if QT_VERSION < 0x050000
template <> \
struct QMetaTypeId< QPair<int,int> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QPair<int,int> >("QPair<int,int>"); \
        return metatype_id; \
    } \
};
#else // QT_VERSION < 0x050000
template <> \
struct QMetaTypeId< QPair<int,int> >
{
    enum { Defined = 1 };
    static int qt_metatype_id()
    {
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);
        if (const int id = metatype_id.loadAcquire())
            return id;
        const int newId = qRegisterMetaType< QPair<int,int> >("QPair<int,int>", reinterpret_cast< QPair<int,int> *>(quintptr(-1)));
        metatype_id.storeRelease(newId);
        return newId;
    }
};
#endif
Q_DECLARE_METATYPE(QAccessibleInterface*)
Q_DECLARE_METATYPE(QAccessibleEvent*)

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
// QAccessible::Text
//

static const QAccessible::Text qtscript_QAccessible_Text_values[] = {
    QAccessible::Name
    , QAccessible::Description
    , QAccessible::Value
    , QAccessible::Help
    , QAccessible::Accelerator
    , QAccessible::DebugDescription
    , QAccessible::UserText
};

static const char * const qtscript_QAccessible_Text_keys[] = {
    "Name"
    , "Description"
    , "Value"
    , "Help"
    , "Accelerator"
    , "DebugDescription"
    , "UserText"
};

static QString qtscript_QAccessible_Text_toStringHelper(QAccessible::Text value)
{
    for (int i = 0; i < 7; ++i) {
        if (qtscript_QAccessible_Text_values[i] == value)
            return QString::fromLatin1(qtscript_QAccessible_Text_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QAccessible_Text_toScriptValue(QScriptEngine *engine, const QAccessible::Text &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAccessible"));
    return clazz.property(qtscript_QAccessible_Text_toStringHelper(value));
}

static void qtscript_QAccessible_Text_fromScriptValue(const QScriptValue &value, QAccessible::Text &out)
{
    out = qvariant_cast<QAccessible::Text>(value.toVariant());
}

static QScriptValue qtscript_construct_QAccessible_Text(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 7; ++i) {
        if (qtscript_QAccessible_Text_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QAccessible::Text>(arg));
    }
    return context->throwError(QString::fromLatin1("Text(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAccessible_Text_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Text value = qscriptvalue_cast<QAccessible::Text>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_Text_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Text value = qscriptvalue_cast<QAccessible::Text>(context->thisObject());
    return QScriptValue(engine, qtscript_QAccessible_Text_toStringHelper(value));
}

static QScriptValue qtscript_create_QAccessible_Text_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAccessible_Text,
        qtscript_QAccessible_Text_valueOf, qtscript_QAccessible_Text_toString);
    qScriptRegisterMetaType<QAccessible::Text>(engine, qtscript_QAccessible_Text_toScriptValue,
        qtscript_QAccessible_Text_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAccessible_Text_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAccessible_Text_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAccessible::RelationFlag
//

static const QAccessible::RelationFlag qtscript_QAccessible_RelationFlag_values[] = {
    QAccessible::AllRelations
    , QAccessible::Label
    , QAccessible::Labelled
    , QAccessible::Controller
    , QAccessible::Controlled
};

static const char * const qtscript_QAccessible_RelationFlag_keys[] = {
    "AllRelations"
    , "Label"
    , "Labelled"
    , "Controller"
    , "Controlled"
};

static QString qtscript_QAccessible_RelationFlag_toStringHelper(QAccessible::RelationFlag value)
{
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QAccessible_RelationFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QAccessible_RelationFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QAccessible_RelationFlag_toScriptValue(QScriptEngine *engine, const QAccessible::RelationFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAccessible"));
    return clazz.property(qtscript_QAccessible_RelationFlag_toStringHelper(value));
}

static void qtscript_QAccessible_RelationFlag_fromScriptValue(const QScriptValue &value, QAccessible::RelationFlag &out)
{
    out = qvariant_cast<QAccessible::RelationFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QAccessible_RelationFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QAccessible_RelationFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QAccessible::RelationFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("RelationFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAccessible_RelationFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::RelationFlag value = qscriptvalue_cast<QAccessible::RelationFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_RelationFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::RelationFlag value = qscriptvalue_cast<QAccessible::RelationFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QAccessible_RelationFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QAccessible_RelationFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAccessible_RelationFlag,
        qtscript_QAccessible_RelationFlag_valueOf, qtscript_QAccessible_RelationFlag_toString);
    qScriptRegisterMetaType<QAccessible::RelationFlag>(engine, qtscript_QAccessible_RelationFlag_toScriptValue,
        qtscript_QAccessible_RelationFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAccessible_RelationFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAccessible_RelationFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAccessible::Relation
//

static QScriptValue qtscript_QAccessible_Relation_toScriptValue(QScriptEngine *engine, const QAccessible::Relation &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QAccessible_Relation_fromScriptValue(const QScriptValue &value, QAccessible::Relation &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QAccessible::Relation>())
        out = qvariant_cast<QAccessible::Relation>(var);
    else if (var.userType() == qMetaTypeId<QAccessible::RelationFlag>())
        out = qvariant_cast<QAccessible::RelationFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QAccessible_Relation(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Relation result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QAccessible::Relation>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QAccessible::RelationFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("Relation(): argument %0 is not of type RelationFlag").arg(i));
            }
            result |= qvariant_cast<QAccessible::RelationFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QAccessible_Relation_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Relation value = qscriptvalue_cast<QAccessible::Relation>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_Relation_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Relation value = qscriptvalue_cast<QAccessible::Relation>(context->thisObject());
    QString result;
    for (int i = 0; i < 5; ++i) {
        if ((value & qtscript_QAccessible_RelationFlag_values[i]) == qtscript_QAccessible_RelationFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QAccessible_RelationFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QAccessible_Relation_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QAccessible::Relation>() == otherObj.value<QAccessible::Relation>())));
}

static QScriptValue qtscript_create_QAccessible_Relation_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QAccessible_Relation, qtscript_QAccessible_Relation_valueOf,
        qtscript_QAccessible_Relation_toString, qtscript_QAccessible_Relation_equals);
    qScriptRegisterMetaType<QAccessible::Relation>(engine, qtscript_QAccessible_Relation_toScriptValue,
        qtscript_QAccessible_Relation_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QAccessible::TextBoundaryType
//

static const QAccessible::TextBoundaryType qtscript_QAccessible_TextBoundaryType_values[] = {
    QAccessible::CharBoundary
    , QAccessible::WordBoundary
    , QAccessible::SentenceBoundary
    , QAccessible::ParagraphBoundary
    , QAccessible::LineBoundary
    , QAccessible::NoBoundary
};

static const char * const qtscript_QAccessible_TextBoundaryType_keys[] = {
    "CharBoundary"
    , "WordBoundary"
    , "SentenceBoundary"
    , "ParagraphBoundary"
    , "LineBoundary"
    , "NoBoundary"
};

static QString qtscript_QAccessible_TextBoundaryType_toStringHelper(QAccessible::TextBoundaryType value)
{
    if ((value >= QAccessible::CharBoundary) && (value <= QAccessible::NoBoundary))
        return qtscript_QAccessible_TextBoundaryType_keys[static_cast<int>(value)-static_cast<int>(QAccessible::CharBoundary)];
    return QString();
}

static QScriptValue qtscript_QAccessible_TextBoundaryType_toScriptValue(QScriptEngine *engine, const QAccessible::TextBoundaryType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAccessible"));
    return clazz.property(qtscript_QAccessible_TextBoundaryType_toStringHelper(value));
}

static void qtscript_QAccessible_TextBoundaryType_fromScriptValue(const QScriptValue &value, QAccessible::TextBoundaryType &out)
{
    out = qvariant_cast<QAccessible::TextBoundaryType>(value.toVariant());
}

static QScriptValue qtscript_construct_QAccessible_TextBoundaryType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAccessible::CharBoundary) && (arg <= QAccessible::NoBoundary))
        return qScriptValueFromValue(engine,  static_cast<QAccessible::TextBoundaryType>(arg));
    return context->throwError(QString::fromLatin1("TextBoundaryType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAccessible_TextBoundaryType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::TextBoundaryType value = qscriptvalue_cast<QAccessible::TextBoundaryType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_TextBoundaryType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::TextBoundaryType value = qscriptvalue_cast<QAccessible::TextBoundaryType>(context->thisObject());
    return QScriptValue(engine, qtscript_QAccessible_TextBoundaryType_toStringHelper(value));
}

static QScriptValue qtscript_create_QAccessible_TextBoundaryType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAccessible_TextBoundaryType,
        qtscript_QAccessible_TextBoundaryType_valueOf, qtscript_QAccessible_TextBoundaryType_toString);
    qScriptRegisterMetaType<QAccessible::TextBoundaryType>(engine, qtscript_QAccessible_TextBoundaryType_toScriptValue,
        qtscript_QAccessible_TextBoundaryType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAccessible_TextBoundaryType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAccessible_TextBoundaryType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAccessible::InterfaceType
//

static const QAccessible::InterfaceType qtscript_QAccessible_InterfaceType_values[] = {
    QAccessible::TextInterface
    , QAccessible::EditableTextInterface
    , QAccessible::ValueInterface
    , QAccessible::ActionInterface
    , QAccessible::ImageInterface
    , QAccessible::TableInterface
    , QAccessible::TableCellInterface
};

static const char * const qtscript_QAccessible_InterfaceType_keys[] = {
    "TextInterface"
    , "EditableTextInterface"
    , "ValueInterface"
    , "ActionInterface"
    , "ImageInterface"
    , "TableInterface"
    , "TableCellInterface"
};

static QString qtscript_QAccessible_InterfaceType_toStringHelper(QAccessible::InterfaceType value)
{
    if ((value >= QAccessible::TextInterface) && (value <= QAccessible::TableCellInterface))
        return qtscript_QAccessible_InterfaceType_keys[static_cast<int>(value)-static_cast<int>(QAccessible::TextInterface)];
    return QString();
}

static QScriptValue qtscript_QAccessible_InterfaceType_toScriptValue(QScriptEngine *engine, const QAccessible::InterfaceType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAccessible"));
    return clazz.property(qtscript_QAccessible_InterfaceType_toStringHelper(value));
}

static void qtscript_QAccessible_InterfaceType_fromScriptValue(const QScriptValue &value, QAccessible::InterfaceType &out)
{
    out = qvariant_cast<QAccessible::InterfaceType>(value.toVariant());
}

static QScriptValue qtscript_construct_QAccessible_InterfaceType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAccessible::TextInterface) && (arg <= QAccessible::TableCellInterface))
        return qScriptValueFromValue(engine,  static_cast<QAccessible::InterfaceType>(arg));
    return context->throwError(QString::fromLatin1("InterfaceType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAccessible_InterfaceType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::InterfaceType value = qscriptvalue_cast<QAccessible::InterfaceType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_InterfaceType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::InterfaceType value = qscriptvalue_cast<QAccessible::InterfaceType>(context->thisObject());
    return QScriptValue(engine, qtscript_QAccessible_InterfaceType_toStringHelper(value));
}

static QScriptValue qtscript_create_QAccessible_InterfaceType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAccessible_InterfaceType,
        qtscript_QAccessible_InterfaceType_valueOf, qtscript_QAccessible_InterfaceType_toString);
    qScriptRegisterMetaType<QAccessible::InterfaceType>(engine, qtscript_QAccessible_InterfaceType_toScriptValue,
        qtscript_QAccessible_InterfaceType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAccessible_InterfaceType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAccessible_InterfaceType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAccessible::Event
//

static const QAccessible::Event qtscript_QAccessible_Event_values[] = {
    QAccessible::SoundPlayed
    , QAccessible::Alert
    , QAccessible::ForegroundChanged
    , QAccessible::MenuStart
    , QAccessible::MenuEnd
    , QAccessible::PopupMenuStart
    , QAccessible::PopupMenuEnd
    , QAccessible::ContextHelpStart
    , QAccessible::ContextHelpEnd
    , QAccessible::DragDropStart
    , QAccessible::DragDropEnd
    , QAccessible::DialogStart
    , QAccessible::DialogEnd
    , QAccessible::ScrollingStart
    , QAccessible::ScrollingEnd
    , QAccessible::MenuCommand
    , QAccessible::ActionChanged
    , QAccessible::ActiveDescendantChanged
    , QAccessible::AttributeChanged
    , QAccessible::DocumentContentChanged
    , QAccessible::DocumentLoadComplete
    , QAccessible::DocumentLoadStopped
    , QAccessible::DocumentReload
    , QAccessible::HyperlinkEndIndexChanged
    , QAccessible::HyperlinkNumberOfAnchorsChanged
    , QAccessible::HyperlinkSelectedLinkChanged
    , QAccessible::HypertextLinkActivated
    , QAccessible::HypertextLinkSelected
    , QAccessible::HyperlinkStartIndexChanged
    , QAccessible::HypertextChanged
    , QAccessible::HypertextNLinksChanged
    , QAccessible::ObjectAttributeChanged
    , QAccessible::PageChanged
    , QAccessible::SectionChanged
    , QAccessible::TableCaptionChanged
    , QAccessible::TableColumnDescriptionChanged
    , QAccessible::TableColumnHeaderChanged
    , QAccessible::TableModelChanged
    , QAccessible::TableRowDescriptionChanged
    , QAccessible::TableRowHeaderChanged
    , QAccessible::TableSummaryChanged
    , QAccessible::TextAttributeChanged
    , QAccessible::TextCaretMoved
    , QAccessible::TextColumnChanged
    , QAccessible::TextInserted
    , QAccessible::TextRemoved
    , QAccessible::TextUpdated
    , QAccessible::TextSelectionChanged
    , QAccessible::VisibleDataChanged
    , QAccessible::ObjectCreated
    , QAccessible::ObjectDestroyed
    , QAccessible::ObjectShow
    , QAccessible::ObjectHide
    , QAccessible::ObjectReorder
    , QAccessible::Focus
    , QAccessible::Selection
    , QAccessible::SelectionAdd
    , QAccessible::SelectionRemove
    , QAccessible::SelectionWithin
    , QAccessible::StateChanged
    , QAccessible::LocationChanged
    , QAccessible::NameChanged
    , QAccessible::DescriptionChanged
    , QAccessible::ValueChanged
    , QAccessible::ParentChanged
    , QAccessible::HelpChanged
    , QAccessible::DefaultActionChanged
    , QAccessible::AcceleratorChanged
    , QAccessible::InvalidEvent
};

static const char * const qtscript_QAccessible_Event_keys[] = {
    "SoundPlayed"
    , "Alert"
    , "ForegroundChanged"
    , "MenuStart"
    , "MenuEnd"
    , "PopupMenuStart"
    , "PopupMenuEnd"
    , "ContextHelpStart"
    , "ContextHelpEnd"
    , "DragDropStart"
    , "DragDropEnd"
    , "DialogStart"
    , "DialogEnd"
    , "ScrollingStart"
    , "ScrollingEnd"
    , "MenuCommand"
    , "ActionChanged"
    , "ActiveDescendantChanged"
    , "AttributeChanged"
    , "DocumentContentChanged"
    , "DocumentLoadComplete"
    , "DocumentLoadStopped"
    , "DocumentReload"
    , "HyperlinkEndIndexChanged"
    , "HyperlinkNumberOfAnchorsChanged"
    , "HyperlinkSelectedLinkChanged"
    , "HypertextLinkActivated"
    , "HypertextLinkSelected"
    , "HyperlinkStartIndexChanged"
    , "HypertextChanged"
    , "HypertextNLinksChanged"
    , "ObjectAttributeChanged"
    , "PageChanged"
    , "SectionChanged"
    , "TableCaptionChanged"
    , "TableColumnDescriptionChanged"
    , "TableColumnHeaderChanged"
    , "TableModelChanged"
    , "TableRowDescriptionChanged"
    , "TableRowHeaderChanged"
    , "TableSummaryChanged"
    , "TextAttributeChanged"
    , "TextCaretMoved"
    , "TextColumnChanged"
    , "TextInserted"
    , "TextRemoved"
    , "TextUpdated"
    , "TextSelectionChanged"
    , "VisibleDataChanged"
    , "ObjectCreated"
    , "ObjectDestroyed"
    , "ObjectShow"
    , "ObjectHide"
    , "ObjectReorder"
    , "Focus"
    , "Selection"
    , "SelectionAdd"
    , "SelectionRemove"
    , "SelectionWithin"
    , "StateChanged"
    , "LocationChanged"
    , "NameChanged"
    , "DescriptionChanged"
    , "ValueChanged"
    , "ParentChanged"
    , "HelpChanged"
    , "DefaultActionChanged"
    , "AcceleratorChanged"
    , "InvalidEvent"
};

static QString qtscript_QAccessible_Event_toStringHelper(QAccessible::Event value)
{
    const QMetaObject *meta = qtscript_QAccessible_metaObject();
    int idx = meta->indexOfEnumerator("Event");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAccessible_Event_toScriptValue(QScriptEngine *engine, const QAccessible::Event &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAccessible"));
    return clazz.property(qtscript_QAccessible_Event_toStringHelper(value));
}

static void qtscript_QAccessible_Event_fromScriptValue(const QScriptValue &value, QAccessible::Event &out)
{
    out = qvariant_cast<QAccessible::Event>(value.toVariant());
}

static QScriptValue qtscript_construct_QAccessible_Event(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAccessible_metaObject();
    int idx = meta->indexOfEnumerator("Event");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAccessible::Event>(arg));
    return context->throwError(QString::fromLatin1("Event(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAccessible_Event_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Event value = qscriptvalue_cast<QAccessible::Event>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_Event_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Event value = qscriptvalue_cast<QAccessible::Event>(context->thisObject());
    return QScriptValue(engine, qtscript_QAccessible_Event_toStringHelper(value));
}

static QScriptValue qtscript_create_QAccessible_Event_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAccessible_Event,
        qtscript_QAccessible_Event_valueOf, qtscript_QAccessible_Event_toString);
    qScriptRegisterMetaType<QAccessible::Event>(engine, qtscript_QAccessible_Event_toScriptValue,
        qtscript_QAccessible_Event_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 69; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAccessible_Event_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAccessible_Event_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAccessible::Role
//

static const QAccessible::Role qtscript_QAccessible_Role_values[] = {
    QAccessible::NoRole
    , QAccessible::TitleBar
    , QAccessible::MenuBar
    , QAccessible::ScrollBar
    , QAccessible::Grip
    , QAccessible::Sound
    , QAccessible::Cursor
    , QAccessible::Caret
    , QAccessible::AlertMessage
    , QAccessible::Window
    , QAccessible::Client
    , QAccessible::PopupMenu
    , QAccessible::MenuItem
    , QAccessible::ToolTip
    , QAccessible::Application
    , QAccessible::Document
    , QAccessible::Pane
    , QAccessible::Chart
    , QAccessible::Dialog
    , QAccessible::Border
    , QAccessible::Grouping
    , QAccessible::Separator
    , QAccessible::ToolBar
    , QAccessible::StatusBar
    , QAccessible::Table
    , QAccessible::ColumnHeader
    , QAccessible::RowHeader
    , QAccessible::Column
    , QAccessible::Row
    , QAccessible::Cell
    , QAccessible::Link
    , QAccessible::HelpBalloon
    , QAccessible::Assistant
    , QAccessible::List
    , QAccessible::ListItem
    , QAccessible::Tree
    , QAccessible::TreeItem
    , QAccessible::PageTab
    , QAccessible::PropertyPage
    , QAccessible::Indicator
    , QAccessible::Graphic
    , QAccessible::StaticText
    , QAccessible::EditableText
    , QAccessible::Button
    , QAccessible::CheckBox
    , QAccessible::RadioButton
    , QAccessible::ComboBox
    , QAccessible::ProgressBar
    , QAccessible::Dial
    , QAccessible::HotkeyField
    , QAccessible::Slider
    , QAccessible::SpinBox
    , QAccessible::Canvas
    , QAccessible::Animation
    , QAccessible::Equation
    , QAccessible::ButtonDropDown
    , QAccessible::ButtonMenu
    , QAccessible::ButtonDropGrid
    , QAccessible::Whitespace
    , QAccessible::PageTabList
    , QAccessible::Clock
    , QAccessible::Splitter
    , QAccessible::LayeredPane
    , QAccessible::Terminal
    , QAccessible::Desktop
    , QAccessible::UserRole
};

static const char * const qtscript_QAccessible_Role_keys[] = {
    "NoRole"
    , "TitleBar"
    , "MenuBar"
    , "ScrollBar"
    , "Grip"
    , "Sound"
    , "Cursor"
    , "Caret"
    , "AlertMessage"
    , "Window"
    , "Client"
    , "PopupMenu"
    , "MenuItem"
    , "ToolTip"
    , "Application"
    , "Document"
    , "Pane"
    , "Chart"
    , "Dialog"
    , "Border"
    , "Grouping"
    , "Separator"
    , "ToolBar"
    , "StatusBar"
    , "Table"
    , "ColumnHeader"
    , "RowHeader"
    , "Column"
    , "Row"
    , "Cell"
    , "Link"
    , "HelpBalloon"
    , "Assistant"
    , "List"
    , "ListItem"
    , "Tree"
    , "TreeItem"
    , "PageTab"
    , "PropertyPage"
    , "Indicator"
    , "Graphic"
    , "StaticText"
    , "EditableText"
    , "Button"
    , "CheckBox"
    , "RadioButton"
    , "ComboBox"
    , "ProgressBar"
    , "Dial"
    , "HotkeyField"
    , "Slider"
    , "SpinBox"
    , "Canvas"
    , "Animation"
    , "Equation"
    , "ButtonDropDown"
    , "ButtonMenu"
    , "ButtonDropGrid"
    , "Whitespace"
    , "PageTabList"
    , "Clock"
    , "Splitter"
    , "LayeredPane"
    , "Terminal"
    , "Desktop"
    , "UserRole"
};

static QString qtscript_QAccessible_Role_toStringHelper(QAccessible::Role value)
{
    const QMetaObject *meta = qtscript_QAccessible_metaObject();
    int idx = meta->indexOfEnumerator("Role");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAccessible_Role_toScriptValue(QScriptEngine *engine, const QAccessible::Role &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAccessible"));
    return clazz.property(qtscript_QAccessible_Role_toStringHelper(value));
}

static void qtscript_QAccessible_Role_fromScriptValue(const QScriptValue &value, QAccessible::Role &out)
{
    out = qvariant_cast<QAccessible::Role>(value.toVariant());
}

static QScriptValue qtscript_construct_QAccessible_Role(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAccessible_metaObject();
    int idx = meta->indexOfEnumerator("Role");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAccessible::Role>(arg));
    return context->throwError(QString::fromLatin1("Role(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAccessible_Role_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Role value = qscriptvalue_cast<QAccessible::Role>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_Role_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Role value = qscriptvalue_cast<QAccessible::Role>(context->thisObject());
    return QScriptValue(engine, qtscript_QAccessible_Role_toStringHelper(value));
}

static QScriptValue qtscript_create_QAccessible_Role_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAccessible_Role,
        qtscript_QAccessible_Role_valueOf, qtscript_QAccessible_Role_toString);
    qScriptRegisterMetaType<QAccessible::Role>(engine, qtscript_QAccessible_Role_toScriptValue,
        qtscript_QAccessible_Role_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 66; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAccessible_Role_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAccessible_Role_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAccessible
//

static QScriptValue qtscript_QAccessible_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAccessible* _q_self = qscriptvalue_cast<QAccessible*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAccessible.%0(): this object is not a QAccessible")
            .arg(qtscript_QAccessible_function_names[_id+6]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QAccessible");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessible_throw_ambiguity_error_helper(context,
        qtscript_QAccessible_function_names[_id+6],
        qtscript_QAccessible_function_signatures[_id+6]);
}

static QScriptValue qtscript_QAccessible_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QAccessible cannot be constructed"));
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = QAccessible::isActive();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        QTextCursor _q_arg0 = qscriptvalue_cast<QTextCursor>(context->argument(0));
        QAccessible::TextBoundaryType _q_arg1 = qscriptvalue_cast<QAccessible::TextBoundaryType>(context->argument(1));
        QPair<int,int> _q_result = QAccessible::qAccessibleTextBoundaryHelper(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QAccessibleInterface* _q_result = QAccessible::queryAccessibleInterface(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QAccessible::setRootObject(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QAccessibleEvent* _q_arg0 = qscriptvalue_cast<QAccessibleEvent*>(context->argument(0));
        QAccessible::updateAccessibility(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessible_throw_ambiguity_error_helper(context,
        qtscript_QAccessible_function_names[_id],
        qtscript_QAccessible_function_signatures[_id]);
}

QScriptValue qtscript_create_QAccessible_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAccessible*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAccessible*)0));

    engine->setDefaultPrototype(qMetaTypeId<QAccessible*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAccessible_static_call, proto, qtscript_QAccessible_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAccessible_static_call,
            qtscript_QAccessible_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QAccessible_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("Text"),
        qtscript_create_QAccessible_Text_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("RelationFlag"),
        qtscript_create_QAccessible_RelationFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Relation"),
        qtscript_create_QAccessible_Relation_class(engine));
    ctor.setProperty(QString::fromLatin1("TextBoundaryType"),
        qtscript_create_QAccessible_TextBoundaryType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("InterfaceType"),
        qtscript_create_QAccessible_InterfaceType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Event"),
        qtscript_create_QAccessible_Event_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Role"),
        qtscript_create_QAccessible_Role_class(engine, ctor));
    return ctor;
}
