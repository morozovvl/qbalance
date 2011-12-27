#include <QtPlugin>

#include "../gui/mytableview.h"
#include "mytableviewplugin.h"

MyTableViewPlugin::MyTableViewPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

bool MyTableViewPlugin::isContainer() const
{
    return false;
}

bool MyTableViewPlugin::isInitialized() const
{
    return m_initialized;
}

QIcon MyTableViewPlugin::icon() const
{
    return QIcon();
}

QString MyTableViewPlugin::codeTemplate() const
{
    return "";
}

QString MyTableViewPlugin::domXml() const
{
    return "<widget class=\"MyTableView\" name=\"myTableView\">\n"
           "</widget>\n";
}

QString MyTableViewPlugin::group() const
{
    return "Your group";
}

QString MyTableViewPlugin::includeFile() const
{
    return "mytableview.h";
}

QString MyTableViewPlugin::name() const
{
    return "MyTableView";
}

QString MyTableViewPlugin::toolTip() const
{
    return "Your tooltip.";
}

QString MyTableViewPlugin::whatsThis() const
{
    return "Your what's this.";
}

QWidget *MyTableViewPlugin::createWidget(QWidget *parent)
{
    return new MyTableView(parent);
}

void MyTableViewPlugin::initialize( QDesignerFormEditorInterface *core )
{
    QDesignerCustomWidgetInterface::initialize(core);
    if( m_initialized )
        return;

    m_initialized = true;
}

