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

#ifndef FORM_H
#define FORM_H

#include <QtXml/QDomDocument>
#include <QtCore/QSettings>
#include <QtCore/QUuid>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtScript/QScriptValue>
#include "mainwindow.h"

class Dialog;
class Essence;


class Form: public QObject
{
    Q_OBJECT
public:
    Form(QObject* parent = 0);
    ~Form();
    Q_INVOKABLE virtual bool open(QWidget* = 0, Essence* = 0, QString = "");
    Q_INVOKABLE virtual void close();
    Q_INVOKABLE Dialog* getFormWidget() { return formWidget; }
    Q_INVOKABLE Essence* getParent() { return parent; }
    Q_INVOKABLE bool isFormSelected() { return lSelected; }
    QString getConfigName() { return configName; }
    void appendToolTip(QString name, QString value);
    virtual void keyPressEvent(QKeyEvent*);

    void setButtonsSignals();
    Q_INVOKABLE bool isDefaultForm() { return defaultForm; }

    Q_INVOKABLE QPushButton* getButtonOk() { return buttonOk; }
    Q_INVOKABLE QPushButton* getButtonCancel() { return buttonCancel; }
    Q_INVOKABLE virtual void setEnabled(bool) { ; }
    virtual void activateWidget() { ; }
    virtual void activateSubWindow();
    void setAutoSelect(bool select) { autoSelect = select; }
    void    readSettings();
    MyMdiSubWindow*     getSubWindow();

public slots:
    Q_INVOKABLE virtual int exec();
    Q_INVOKABLE virtual void show();
    Q_INVOKABLE virtual void hide();
    virtual void cmdOk();
    virtual void cmdCancel();
    virtual void buttonPressedSignalSend() { emit buttonPressed(sender()->objectName()); }
    Q_INVOKABLE virtual void gotoCenter();

signals:
    void buttonPressed(QString);


protected:
    TApplication*   app;
    DBFactory*      db;
    Dialog*         formWidget;
    MyMdiSubWindow* subWindow;
    Essence*        parent;
    bool            lSelected;
    bool            defaultForm;
    bool            appendToMdi;        // Флаг, указывающий, нужно ли добавлять окно к многооконному интерфейсу
                                        // Для большинства окон - надо, но для некоторых нет (ConnectionForm, PasswordForm)
    QString         configName;
    QString         fileName;

    QString         script;
    QScriptValue    scripts;

    QHBoxLayout*    cmdButtonLayout;
    QVBoxLayout*    vbxLayout;
    QPushButton*    buttonOk;
    QPushButton*    buttonCancel;

    virtual void    createForm(QString, QWidget* pwgt = 0);
    void            writeSettings();

private:
    bool                    uiCreated;
    QMap<QString, QString>  toolTips;
    bool                    freeWindow;         // По умолчанию окно не является свободным, я является частью Mdi интерфейса
    bool                    autoSelect;

    void                    checkVisibility();
};

#endif
