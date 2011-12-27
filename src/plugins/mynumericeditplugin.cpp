#include <QtPlugin>
#include "../gui/mynumericedit.h"
#include "mynumericeditplugin.h"

MyNumericEditPlugin::MyNumericEditPlugin( QObject *parent ) : QObject(parent) {
    m_initialized = false;
}

bool MyNumericEditPlugin::isContainer() const {
    return false;
}

bool MyNumericEditPlugin::isInitialized() const {
    return m_initialized;
}

QIcon MyNumericEditPlugin::icon() const {
    return QIcon();
}

QString MyNumericEditPlugin::codeTemplate() const {
    return "";
}

QString MyNumericEditPlugin::domXml() const {
    return "<widget class=\"MyNumericEdit\" name=\"myNumericEdit\">\n"
           "</widget>\n";
}

QString MyNumericEditPlugin::group() const {
    return "Your group";
}

QString MyNumericEditPlugin::includeFile() const {
    return "mynumericedit.h";
}

QString MyNumericEditPlugin::name() const {
    return "MyNumericEdit";
}

QString MyNumericEditPlugin::toolTip() const {
    return "Your tooltip.";
}

QString MyNumericEditPlugin::whatsThis() const {
    return "Your what's this.";
}

QWidget *MyNumericEditPlugin::createWidget( QWidget *parent ) {
    return new MyNumericEdit(parent);
}

void MyNumericEditPlugin::initialize( QDesignerFormEditorInterface *core ) {
    QDesignerCustomWidgetInterface::initialize(core);
    if( m_initialized )
        return;

    m_initialized = true;
}
