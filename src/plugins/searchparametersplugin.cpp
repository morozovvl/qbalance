#include <QtPlugin>

#include "../gui/searchparameters.h"
#include "searchparametersplugin.h"

SearchParametersPlugin::SearchParametersPlugin(QObject *parent) : QObject(parent) {
    m_initialized = false;
}

bool SearchParametersPlugin::isContainer() const {
    return false;
}

bool SearchParametersPlugin::isInitialized() const {
    return m_initialized;
}

QIcon SearchParametersPlugin::icon() const {
    return QIcon(":searchparameters");
}

QString SearchParametersPlugin::codeTemplate() const {
    return "";
}

QString SearchParametersPlugin::domXml() const {
    return "<widget class=\"SearchParameters\" name=\"searchParameters\">\n"
           "</widget>\n";
}

QString SearchParametersPlugin::group() const {
    return "Your group";
}

QString SearchParametersPlugin::includeFile() const {
    return "searchparameters.h";
}

QString SearchParametersPlugin::name() const {
    return "SearchParameters";
}

QString SearchParametersPlugin::toolTip() const {
    return "Your tooltip.";
}

QString SearchParametersPlugin::whatsThis() const {
    return "Your what's this.";
}

QWidget *SearchParametersPlugin::createWidget(QWidget *parent ) {
    return new SearchParameters(parent);
}

void SearchParametersPlugin::initialize( QDesignerFormEditorInterface *core ) {
    QDesignerCustomWidgetInterface::initialize(core);
    if( m_initialized )
        return;
    m_initialized = true;
}
