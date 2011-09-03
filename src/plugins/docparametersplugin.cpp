#include <QtPlugin>

#include "../gui/docparameters.h"
#include "docparametersplugin.h"

DocParametersPlugin::DocParametersPlugin( QObject *parent ) : QObject(parent) {
    m_initialized = false;
}

bool DocParametersPlugin::isContainer() const {
    return false;
}

bool DocParametersPlugin::isInitialized() const {
    return m_initialized;
}

QIcon DocParametersPlugin::icon() const {
    return QIcon();
}

QString DocParametersPlugin::codeTemplate() const {
    return "";
}

QString DocParametersPlugin::domXml() const {
    return "<widget class=\"DocParameters\" name=\"docParameters\">\n"
           "</widget>\n";
}

QString DocParametersPlugin::group() const {
    return "Your group";
}

QString DocParametersPlugin::includeFile() const {
    return "docparameters.h";
}

QString DocParametersPlugin::name() const {
    return "DocParameters";
}

QString DocParametersPlugin::toolTip() const {
    return "Your tooltip.";
}

QString DocParametersPlugin::whatsThis() const {
    return "Your what's this.";
}

QWidget *DocParametersPlugin::createWidget(QWidget *parent ) {
    return new DocParameters(parent);
}

void DocParametersPlugin::initialize( QDesignerFormEditorInterface *core ) {
    QDesignerCustomWidgetInterface::initialize(core);
    if( m_initialized )
        return;
    m_initialized = true;
}
