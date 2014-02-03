#include "plugin.h"

QStringList com_trolltech_qt_svg_ScriptPlugin::keys() const
{
    QStringList list;
    list << QLatin1String("qt");
    list << QLatin1String("qt.svg");
    return list;
}

void com_trolltech_qt_svg_ScriptPlugin::initialize(const QString &key, QScriptEngine *engine)
{
    if (key == QLatin1String("qt")) {
    } else if (key == QLatin1String("qt.svg")) {
        QScriptValue extensionObject = engine->globalObject();
        qtscript_initialize_com_trolltech_qt_svg_bindings(extensionObject);
    } else {
        Q_ASSERT_X(false, "com_trolltech_qt_svg::initialize", qPrintable(key));
    }
}

#if QT_VERSION < 0x050000
Q_EXPORT_STATIC_PLUGIN(com_trolltech_qt_svg_ScriptPlugin)
Q_EXPORT_PLUGIN2(qtscript_com_trolltech_qt_svg, com_trolltech_qt_svg_ScriptPlugin)
#endif
