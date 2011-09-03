#include <QtPlugin>

#include "../gui/picture.h"
#include "pictureplugin.h"

PicturePlugin::PicturePlugin( QObject *parent ) : QObject(parent) {
    m_initialized = false;
}

bool PicturePlugin::isContainer() const {
    return false;
}

bool PicturePlugin::isInitialized() const {
    return m_initialized;
}

QIcon PicturePlugin::icon() const {
    return QIcon();
}

QString PicturePlugin::codeTemplate() const {
    return "";
}

QString PicturePlugin::domXml() const {
    return "<widget class=\"Picture\" name=\"picture\">\n"
           "</widget>\n";
}

QString PicturePlugin::group() const {
    return "Your group";
}

QString PicturePlugin::includeFile() const {
    return "picture.h";
}

QString PicturePlugin::name() const {
    return "Picture";
}

QString PicturePlugin::toolTip() const {
    return "Your tooltip.";
}

QString PicturePlugin::whatsThis() const {
    return "Your what's this.";
}

QWidget *PicturePlugin::createWidget( QWidget *parent ) {
    return new Picture(parent);
}

void PicturePlugin::initialize( QDesignerFormEditorInterface *core ) {
    QDesignerCustomWidgetInterface::initialize(core);
    if( m_initialized )
        return;

    m_initialized = true;
}
