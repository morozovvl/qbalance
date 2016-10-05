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

#ifndef CONNECTIONFORM_H
#define CONNECTIONFORM_H

#define CONNECTION_GROUP_NAME   "connections"

#include <QtCore/QString>
#include <QtGui/QComboBox>
#include <QtGui/QLineEdit>
#include "form.h"

class TApplication;
class DBFactory;

class ConnectionForm : public Form {
    Q_OBJECT
public:
    ConnectionForm(QObject* parent = 0);
    ~ConnectionForm();
    virtual void initForm(QString, QString, int, bool readSettings = true);
    QString connectionName();
public slots:
    virtual int exec(DBFactory*);
protected:
    void readSettings(QString);
    void writeSettings();
private slots:
    void buttonSave();
    void buttonDelete();
    void cmdOk();
    void cmdCancel();
    void connectionChanged(int);
private:
    DBFactory* db;
    QComboBox* pcmbConnection;
    QLineEdit* ptxtHost;
    QLineEdit* ptxtPort;
    QLineEdit* ptxtDatabase;
    void readConnectionsList();
    void readDefaultSettings();
    void writeDefaultSettings();
    void deleteSettings(QString);
};

#endif // CONNECTIONFORM_H
