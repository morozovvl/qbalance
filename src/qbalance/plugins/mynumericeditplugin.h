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

#ifndef MYNUMERICEDITPLUGIN_H
#define MYNUMERICEDITPLUGIN_H

#include <QLineEdit>
#include <QtDesigner/QDesignerCustomWidgetInterface>

class MyNumericEditPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    MyNumericEditPlugin( QObject *parent = 0 );

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString codeTemplate() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget( QWidget *parent );
    void initialize( QDesignerFormEditorInterface *core );

private:
    bool m_initialized;
};
#endif // MYNUMERICEDITPLUGIN_H


