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
           "<layout class=\"QGridLayout\" name=\"gridLayout\"/>\n"
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
