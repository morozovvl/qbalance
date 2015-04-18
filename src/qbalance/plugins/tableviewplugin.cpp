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

#include "../gui/tableview.h"
#include "tableviewplugin.h"

TableViewPlugin::TableViewPlugin(QObject *parent) : QObject(parent) {
    m_initialized = false;
}

bool TableViewPlugin::isContainer() const {
    return true;
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
    return  "<ui language=\"c++\"> displayname=\"TableView\">\n"
            "   <widget class=\"TableView\" name=\"tableView\"/>\n"
            "   <customwidgets>\n"
            "       <customwidget>\n"
            "           <class>TableView</class>\n"
            "           <addpagemethod>addPage</addpagemethod>\n"
//            "           <propertyspecifications>\n"
//            "               <stringpropertyspecification name=\"fileName\" notr=\"true\" type=\"singleline\"\n"
//            "               <stringpropertyspecification name=\"text\" type=\"richtext\"\n"
//            "           </propertyspecifications>\n"
            "       </customwidget>\n"
            "   </customwidgets>\n"
            "</ui>\n";
//    return "<widget class=\"TableView\" name=\"tableView\">\n"
//           "</widget>\n";
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

