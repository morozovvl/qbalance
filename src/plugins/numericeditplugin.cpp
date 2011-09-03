#include <QtPlugin>
#include "../gui/numericedit.h"
#include "numericeditplugin.h"

NumericEditPlugin::NumericEditPlugin( QObject *parent ) : QObject(parent) {
    m_initialized = false;
}

bool NumericEditPlugin::isContainer() const {
    return false;
}

bool NumericEditPlugin::isInitialized() const {
    return m_initialized;
}

QIcon NumericEditPlugin::icon() const {
    return QIcon();
}

QString NumericEditPlugin::codeTemplate() const {
    return "";
}

QString NumericEditPlugin::domXml() const {
    return "<widget class=\"NumericEdit\" name=\"numericEdit\">\n"
           "</widget>\n";
}

QString NumericEditPlugin::group() const {
    return "Your group";
}

QString NumericEditPlugin::includeFile() const {
    return "numericedit.h";
}

QString NumericEditPlugin::name() const {
    return "NumericEdit";
}

QString NumericEditPlugin::toolTip() const {
    return "Your tooltip.";
}

QString NumericEditPlugin::whatsThis() const {
    return "Your what's this.";
}

QWidget *NumericEditPlugin::createWidget( QWidget *parent ) {
    return new NumericEdit(parent);
}

void NumericEditPlugin::initialize( QDesignerFormEditorInterface *core ) {
    QDesignerCustomWidgetInterface::initialize(core);
    if( m_initialized )
        return;

    m_initialized = true;
}
