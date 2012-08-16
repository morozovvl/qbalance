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

#include <QtGui>
#include <QDomDocument>
#include <QSettings>
#include <QUuid>
#include "../engine/scriptengine.h"
#include "../kernel/essence.h"

class Form: public QObject
{
    Q_OBJECT
public:
    explicit Form(QObject* parent = NULL);
    ~Form();
    Q_INVOKABLE virtual bool open(QWidget* = 0, Essence* = 0, QString = "");
    Q_INVOKABLE virtual void close();
    Q_INVOKABLE virtual void setIcons();
    Q_INVOKABLE Dialog* getForm() { return formWidget; }
    Q_INVOKABLE Essence* getParent() { return parent; }
    Q_INVOKABLE bool selected() { return lSelected; }
    Q_INVOKABLE bool opened() { return (formWidget != 0) ? true : false; }
    void setConfigName(QString name) { configName = name; setObjectName(configName); }
    QString getConfigName() { return configName; }
    virtual void readSettings();
    virtual void writeSettings();
    virtual void createUi();
    void initFormEvent();
    void beforeShowFormEvent();
    void afterHideFormEvent();
    void closeFormEvent();
    void setButtonsSignals();
    ScriptEngine* getScriptEngine() { return parent->getScriptEngine(); }
    bool isDefaultForm() { return defaultForm; }
    QPushButton*    getButtonOk() {  return buttonOk; }
    QPushButton*    getButtonCancel() { return buttonCancel; }

public slots:
    Q_INVOKABLE virtual int exec();
    Q_INVOKABLE virtual void show();
    Q_INVOKABLE virtual void hide();
    Q_INVOKABLE virtual void cmdOk();
    Q_INVOKABLE virtual void cmdCancel();
    virtual void buttonPressedSignalSend() { emit buttonPressed(sender()->objectName()); }

signals:
    void buttonPressed(QString);


protected:
    DBFactory*      db;
    Dialog*        formWidget;
    Essence*        parent;
    bool            lSelected;
    bool            defaultForm;
    QString         configName;
    QString         fileName;
    bool            iconsSeted;

    QString         script;
    QScriptValue    scripts;

    QHBoxLayout*    cmdButtonLayout;
    QVBoxLayout*    vbxLayout;
    QPushButton*    buttonOk;
    QPushButton*    buttonCancel;

    virtual void createForm(QString, QWidget* pwgt = 0);
    virtual QDomElement createWidgetsStructure();
    QDomElement createBoxLayoutElement(QLayout*);
    QDomElement createPushButtonElement(QWidget*);
    QDomElement createLabelElement(QString);
    QDomElement createLineEditElement(QLineEdit*);
    QDomElement createDateEditElement(QDateEdit*);
    QDomElement createHStretchElement();
    QDomElement createVStretchElement();
    QDomElement createConnectionElement(QWidget*, QString, QWidget*, QString);

private:
    bool uiCreated;
};

#endif
