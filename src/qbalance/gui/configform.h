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

#ifndef CONFIGFORM_H
#define CONFIGFORM_H

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QFrame>
    #include <QtGui/QComboBox>
    #include <QtGui/QCheckBox>
    #include <QtGui/QTreeWidgetItem>
#else
    #include <QtWidgets/QFrame>
    #include <QtWidgets/QComboBox>
    #include <QtWidgets/QCheckBox>
    #include <QtWidgets/QTreeWidgetItem>
#endif


#include <QtCore/QSignalMapper>
#include "../kernel/configvars.h"
#include "form.h"

class TApplication;

struct ConfigEntry;

class ConfigForm : public Form
{
    Q_OBJECT
public:
    QSignalMapper *signalMapper;

    ConfigForm(QObject* parent = 0);
    ~ConfigForm();
    virtual bool open(QWidget* pwgt = 0);

public slots:
    virtual void cmdOk();
    virtual void buttonPressed(QString);

private slots:
    void dispatch(QTreeWidgetItem*, int);

private:
    TApplication* app;
    QFrame* frame;
    QHash<QString, ConfigEntry> configs;
    QString                     currentConfigGroup;

    void dictAdd();
    void dictProperties();
    void dictColumns();
    void dictPermissions();

    void showConfigGroup(QString);
    void changePassword();
    void ftpTotalUpload();
    void ftpUpload();
    void ftpLoad();
};

#endif // CONFIGFORM_H
