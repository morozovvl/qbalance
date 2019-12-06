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

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QPushButton>
    #include <QtGui/QDesktopWidget>
    #include <QtGui/QToolTip>
    #include <QtGui/QMdiSubWindow>
#else
    #include <QtWidgets/QPushButton>
    #include <QtWidgets/QDesktopWidget>
    #include <QtWidgets/QToolTip>
    #include <QtWidgets/QMdiSubWindow>
#endif

#include <QtXml/QDomDocument>
#include <QtCore/QSettings>
#include <QtCore/QUuid>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtScript/QScriptValue>
//#include <QtWidgets/QPrinter>
//#include "mainwindow.h"
//#include "../kernel/essence.h"

class Dialog;
class Dictionary;
class Essence;
class TApplication;
class DBFactory;


class Form: public QObject
{
    Q_OBJECT
public:
    Form(QObject* parent = nullptr);
    ~Form();
    Q_INVOKABLE virtual bool open(QWidget* = nullptr, Essence* = nullptr, QString = "");
    Q_INVOKABLE virtual void close();
    Q_INVOKABLE virtual Dialog* getFormWidget();
    Q_INVOKABLE virtual bool isVisible();
    Q_INVOKABLE virtual Dictionary* getParent();
    Q_INVOKABLE virtual bool isFormSelected();
    virtual QString getConfigName();
    virtual void appendToolTip(QString name, QString value);
    virtual void keyPressEvent(QKeyEvent*);

    virtual void setButtonsSignals();
    Q_INVOKABLE virtual bool isDefaultForm();

    Q_INVOKABLE virtual QPushButton* addButton(QString);
    Q_INVOKABLE virtual QPushButton* insertButton(QString, int = 0);
    Q_INVOKABLE virtual QPushButton* getButtonOk();
    Q_INVOKABLE virtual QPushButton* getButtonCancel();

    Q_INVOKABLE virtual void setEnabled(bool);
    virtual void activateWidget() { ; }
    virtual void activateSubWindow();
    Q_INVOKABLE virtual void readSettings();
    Q_INVOKABLE virtual void writeSettings();
    Q_INVOKABLE virtual QMdiSubWindow*     getSubWindow();
    virtual TApplication*      getApp();

    Q_INVOKABLE virtual QString getFormTitle();
    Q_INVOKABLE virtual void setFormTitle(QString);

public slots:
    Q_INVOKABLE virtual int exec();
    Q_INVOKABLE virtual void show();
    Q_INVOKABLE virtual void hide();
    Q_INVOKABLE virtual void cmdOk();
    Q_INVOKABLE virtual void cmdCancel();
    virtual void buttonPressedSignalSend();
    Q_INVOKABLE virtual void gotoCenter();

signals:
    void buttonPressed(QString);


protected:
    TApplication*   app;
    DBFactory*      db;
    Dialog*         formWidget;
    QMdiSubWindow*  subWindow;
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
    bool            enabled;

    virtual void    createForm(QString, QWidget* pwgt = nullptr);

private:
    bool                    uiCreated;
    QHash<QString, QString>  toolTips;
    bool                    freeWindow;         // По умолчанию окно не является свободным, я является частью Mdi интерфейса

    void                    checkVisibility();
};

#endif
