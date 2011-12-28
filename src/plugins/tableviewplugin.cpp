//#include <QtPlugin>

#include "../gui/tableview.h"
#include "tableviewplugin.h"

TableViewPlugin::TableViewPlugin(QObject *parent) : QObject(parent) {
    m_initialized = false;
}

bool TableViewPlugin::isContainer() const {
    return false;
}

bool TableViewPlugin::isInitialized() const {
    return m_initialized;
}

QIcon TableViewPlugin::icon() const {
    return QIcon();
}

QString TableViewPlugin::codeTemplate() const {
    return "";
}

QString TableViewPlugin::domXml() const {
    return "<widget class=\"TableView\" name=\"tableView\">\n"
           "</widget>\n";
}

QString TableViewPlugin::group() const {
    return "Your group";
}

QString TableViewPlugin::includeFile() const {
    return "tableview.h";
}

QString TableViewPlugin::name() const {
    return "TableView";
}

QString TableViewPlugin::toolTip() const {
    return "Your tooltip.";
}

QString TableViewPlugin::whatsThis() const {
    return "Your what's this.";
}

QWidget *TableViewPlugin::createWidget(QWidget *parent) {
    return new TableView(parent);
}

void TableViewPlugin::initialize( QDesignerFormEditorInterface *core ) {
    QDesignerCustomWidgetInterface::initialize(core);
    if( m_initialized )
        return;

    m_initialized = true;
}

