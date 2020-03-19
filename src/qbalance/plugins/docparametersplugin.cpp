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


