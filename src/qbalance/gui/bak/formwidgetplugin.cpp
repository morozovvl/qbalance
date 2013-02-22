#include "formwidgetplugin.h"
#include "form.h"
#include <QtPlugin>

FormWidgetPlugin::FormWidgetPlugin(QObject *parent) : QObject(parent) {
    initialized = false;
}

void FormWidgetPlugin::initialize(QDesignerFormEditorInterface *) {
    if (initialized)
        return;
    initialized = true;
}

bool FormWidgetPlugin::isInitialized() const {
    return initialized;
}

QWidget *FormWidgetPlugin::createWidget(QWidget *parent) {
    return new Form(parent);
}

QString FormWidgetPlugin::name() const {
    return "form";
}

QString FormWidgetPlugin::group() const {
    return "Display Widgets [Examples]";
}

QIcon FormWidgetPlugin::icon() const {
    return QIcon();
}

QString FormWidgetPlugin::toolTip() const {
    return "";
}

QString FormWidgetPlugin::whatsThis() const {
    return "";
}

bool FormWidgetPlugin::isContainer() const {
    return false;
}

QString FormWidgetPlugin::domXml() const {
    return "<widget class=\"AnalogClock\" name=\"analogClock\">\n"
           " <property name=\"geometry\">\n"
           "  <rect>\n"
           "   <x>0</x>\n"
           "   <y>0</y>\n"
           "   <width>100</width>\n"
           "   <height>100</height>\n"
           "  </rect>\n"
           " </property>\n"
           " <property name=\"toolTip\" >\n"
           "  <string>The current time</string>\n"
           " </property>\n"
           " <property name=\"whatsThis\" >\n"
           "  <string>The analog clock widget displays "
           "the current time.</string>\n"
           " </property>\n"
           "</widget>\n";
}

QString FormWidgetPlugin::includeFile() const {
    return "form.h";
}

Q_EXPORT_PLUGIN2(customwidgetplugin, FormWidgetPlugin)

