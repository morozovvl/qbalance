#ifndef ESSENCE_H
#define ESSENCE_H

#define DEFAULT_REPORT "default_report.ods"          // Отчет будем готовить в формате Open Office 1.0 (запакованный ZIP-ом каталог с XML файлами)
#define REPORT_DIR      "./reports/"
#define TMP_DIR         "./tmp/"

#include <QVariant>
#include <QString>
#include <QStringList>
#include <QSqlTableModel>
#include <QProcess>
#include <QDomNode>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QDialog>
#include "table.h"
#include "scriptengine.h"

class App;
extern App* app;

class FormGrid;

class Essence : public Table {
    Q_OBJECT

public:
    Essence(QString name = "", QObject *parent = 0);
    ~Essence();
    virtual bool calculate(const QModelIndex &);
    virtual void setOldCalculateProperties(const QModelIndex &);
    virtual void revertCalculateProperties(const QModelIndex &);
    virtual qulonglong getId(int row = 0);
    virtual void setId(qulonglong);
    QString getIdFieldName() { return idFieldName; }
    virtual bool isFieldExists(QString field) { return getFieldsList().contains(field); }
    virtual QVariant getValue(QString, int row = -1);                 // Возвращает значение заданного поля в текущей записи
    virtual bool setValue(QString, QVariant, int row = -1);           // Устанавливает значение заданного поля в текущей записи
    virtual FormGrid* getForm() { return form; }
    void setScriptForTable(QString);
    virtual bool add() { return false; }
    virtual bool remove();
    virtual void view();
    virtual void print(QString);
    virtual void cmdOk();
    virtual void cmdCancel();
    virtual QSqlQuery getColumnsHeaders();
    bool isInsertable() { return lInsertable; }
    bool isDeleteable() { return lDeleteable; }
    bool isViewable() { return lViewable; }
    bool isUpdateable() { return lUpdateable; }
    bool isPrintable() { return lPrintable; }
    void setInsertable(bool b) { lInsertable = b; }
    void setDeleteable(bool b) { lDeleteable = b; }
    void setViewable(bool b) { lViewable = b; }
    void setUpdateable(bool b) { lUpdateable = b; }
    void setPrintable(bool b) { lPrintable = b; }
    QString getPhotoPath();

    Q_INVOKABLE virtual bool isFormSelected();
    Q_INVOKABLE virtual int exec();
    Q_INVOKABLE virtual void show();
    Q_INVOKABLE virtual void hide();
    Q_INVOKABLE void setFormTitle(QString);
    Q_INVOKABLE virtual QDialog* getFormWidget();
signals:
    void showError(const QString &);

protected:
    QString             formTitle;
    QString             idFieldName;
    FormGrid*           form;
    QWidget*            parentForm;
    ScriptEngine*       engine;
    QString             script;
    QScriptValue        scripts;
    bool lInsertable;
    bool lDeleteable;
    bool lViewable;
    bool lUpdateable;
    bool lPrintable;
    virtual void setForm();
    void initForm();
    virtual bool doOpen();
    virtual void doClose();
    virtual void getCalculateProperties(const QModelIndex &);
    virtual void setCalculateProperties(const QModelIndex &);
    virtual void preparePrintValues(QMap<QString, QVariant>*);     // Готовит значения для печати
};

#endif // ESSENCE_H
