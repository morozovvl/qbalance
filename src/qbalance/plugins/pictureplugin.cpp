/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/

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
