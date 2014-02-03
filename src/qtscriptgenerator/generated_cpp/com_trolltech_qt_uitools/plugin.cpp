#include "plugin.h"

QStringList com_trolltech_qt_uitools_ScriptPlugin::keys() const
{
    QStringList list;
    list << QLatin1String("qt");
    list << QLatin1String("qt.uitools");
    return list;
}

void com_trolltech_qt_uitools_ScriptPlugin::initialize(const QString &key, QScriptEngine *engine)
{
    if (key == QLatin1String("qt")) {
    } else if (key == QLatin1String("qt.uitools")) {
        QScriptValue extensionObject = engine->globalObject();
        qtscript_initialize_com_trolltech_qt_uitools_bindings(extensionObject);
    } else {
        Q_ASSERT_X(false, "com_trolltech_qt_uitools::initialize", qPrintable(key));
    }
}

#if QT_VERSION < 0x050000
Q_EXPORT_STATIC_PLUGIN(com_trolltech_qt_uitools_ScriptPlugin)
Q_EXPORT_PLUGIN2(qtscript_com_trolltech_qt_uitools, com_trolltech_qt_uitools_ScriptPlugin)
#endif
