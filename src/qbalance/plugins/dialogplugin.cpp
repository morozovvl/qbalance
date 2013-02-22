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

#include "../gui/dialog.h"
#include "dialogplugin.h"

DialogPlugin::DialogPlugin(QObject *parent) : QObject(parent) {
    m_initialized = false;
}

bool DialogPlugin::isContainer() const {
    return false;
}

bool DialogPlugin::isInitialized() const {
    return m_initialized;
}

QIcon DialogPlugin::icon() const {
    return QIcon();
}

QString DialogPlugin::codeTemplate() const {
    return "";
}

QString DialogPlugin::domXml() const {
    return "<widget class=\"Dialog\" name=\"Dialog\">\n"
           "</widget>\n";
}

QString DialogPlugin::group() const {
    return "Your group";
}

QString DialogPlugin::includeFile() const {
    return "dialog.h";
}

QString DialogPlugin::name() const {
    return "Dialog";
}

QString DialogPlugin::toolTip() const {
    return "Your tooltip.";
}

QString DialogPlugin::whatsThis() const {
    return "Your what's this.";
}

QWidget *DialogPlugin::createWidget(QWidget *parent) {
    return new Dialog(parent);
}

void DialogPlugin::initialize( QDesignerFormEditorInterface *core ) {
    QDesignerCustomWidgetInterface::initialize(core);
    if( m_initialized )
        return;

    m_initialized = true;
}

