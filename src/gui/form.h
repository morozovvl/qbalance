#ifndef FORM_H
#define FORM_H

#include <QtGui>
#include <QDomDocument>
#include <QSettings>
#include <QUuid>
#include "../engine/scriptengine.h"

class Essence;

class Form: public QObject
{
    Q_OBJECT
public:
    explicit Form(QObject* parent = NULL);
    Q_INVOKABLE virtual bool open(QWidget* pwgt = 0, Essence* par = 0);
    Q_INVOKABLE virtual bool open(QString, QWidget* form = 0);
    Q_INVOKABLE virtual void close();
    void setConfigName(QString name) { configName = name; setObjectName(configName); }
    QString getConfigName() { return configName; }
    Q_INVOKABLE virtual void setIcons();
    virtual void readSettings();
    virtual void writeSettings();
    virtual void createUi();
    ScriptEngine* getScriptEngine() { return engine; }
    void initFormEvent();
    void beforeShowFormEvent();
    void afterHideFormEvent();
    void closeFormEvent();
    void setScriptForForm(QString);
    void removeScriptForForm();
    void setButtonsSignals();

    Q_INVOKABLE QDialog* getForm() { return formWidget; }
    Q_INVOKABLE Essence* getParent() { return parent; }
    Q_INVOKABLE bool selected() { return lSelected; }
    Q_INVOKABLE bool opened() { return (formWidget != 0) ? true : false; }

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
    QDialog*        formWidget;
    Essence*        parent;
    bool            lSelected;
    bool            defaultForm;
    QString         configName;
    bool            iconsSeted;

    ScriptEngine*   engine;
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
