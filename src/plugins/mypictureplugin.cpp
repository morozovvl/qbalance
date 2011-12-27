#include <QtPlugin>

#include "../gui/mypicture.h"
#include "mypictureplugin.h"

MyPicturePlugin::MyPicturePlugin( QObject *parent ) : QObject(parent)
{
    m_initialized = false;
}

bool MyPicturePlugin::isContainer() const
{
    return false;
}

bool MyPicturePlugin::isInitialized() const
{
    return m_initialized;
}

QIcon MyPicturePlugin::icon() const
{
    return QIcon();
}

QString MyPicturePlugin::codeTemplate() const
{
    return "";
}

QString MyPicturePlugin::domXml() const
{
    return "<widget class=\"MyPicture\" name=\"myPicture\">\n"
           "</widget>\n";
}

QString MyPicturePlugin::group() const
{
    return "Your group";
}

QString MyPicturePlugin::includeFile() const
{
    return "mypicture.h";
}

QString MyPicturePlugin::name() const
{
    return "MyPicture";
}

QString MyPicturePlugin::toolTip() const
{
    return "Your tooltip.";
}

QString MyPicturePlugin::whatsThis() const
{
    return "Your what's this.";
}

QWidget *MyPicturePlugin::createWidget( QWidget *parent )
{
    return new MyPicture(parent);
}

void MyPicturePlugin::initialize( QDesignerFormEditorInterface *core )
{
    QDesignerCustomWidgetInterface::initialize(core);
    if( m_initialized )
        return;

    m_initialized = true;
}

//Q_EXPORT_PLUGIN2(mypictureplugin, MyPicturePlugin)

