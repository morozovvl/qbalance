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
