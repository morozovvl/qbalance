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
#include "../storage/table.h"
#include "../engine/scriptengine.h"

class TApplication;

class FormGrid;

class Essence : public Table {
    Q_OBJECT

public:
    Essence(QString name = "", QObject *parent = 0);
    ~Essence();
// Функции для получения, сохранения данных модели
    virtual qulonglong getId(int row = 0);
    virtual void setId(qulonglong);
    QString getIdFieldName() { return idFieldName; }
    virtual bool isFieldExists(QString field) { return getFieldsList().contains(field); }
    virtual QVariant getValue(QString, int row = -1);                 // Возвращает значение заданного поля в текущей записи
    virtual bool setValue(QString, QVariant, int row = -1);           // Устанавливает значение заданного поля в текущей записи
    virtual bool add() { return false; }        // Добавление записи
    virtual bool remove();                      // Удаление записи

// Функции для работы с модулем GUI
    virtual FormGrid* getForm() { return form; }
    virtual void cmdOk();                       // Обработка нажатий кнопок "Ok"
    virtual void cmdCancel();                   // и "Cancel"
    Q_INVOKABLE virtual bool isFormSelected();
    Q_INVOKABLE virtual int exec();                 // Показать форму в модальном режиме
    Q_INVOKABLE virtual void show();                // Показать форму в немодальном режиме
    Q_INVOKABLE virtual void hide();                // Скрыть форму
    Q_INVOKABLE void setFormTitle(QString);         // Установить заголовок формы
    Q_INVOKABLE virtual QDialog* getFormWidget();
    virtual void view();
    virtual void print(QString);
    bool isInsertable() { return lInsertable; }         // Получить/установить ...
    bool isDeleteable() { return lDeleteable; }         // ... свойства отображения ...
    bool isViewable() { return lViewable; }             // ... кнопок на форме
    bool isUpdateable() { return lUpdateable; }
    bool isPrintable() { return lPrintable; }
    void setInsertable(bool b) { lInsertable = b; }
    void setDeleteable(bool b) { lDeleteable = b; }
    void setViewable(bool b) { lViewable = b; }
    void setUpdateable(bool b) { lUpdateable = b; }
    void setPrintable(bool b) { lPrintable = b; }

// Функции для обеспечения работы скриптов
    virtual bool calculate(const QModelIndex &);
    virtual void setOldCalculateProperties(const QModelIndex &);
    virtual void revertCalculateProperties(const QModelIndex &);
    void setScriptForTable(QString);

// Прочие функции
    virtual QSqlQuery getColumnsHeaders();
    QString getPhotoPath();
    Q_INVOKABLE virtual void close();

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
    bool                lInsertable;
    bool                lDeleteable;
    bool                lViewable;
    bool                lUpdateable;
    bool                lPrintable;
    virtual void setForm();
    void initForm();
    virtual void getCalculateProperties(const QModelIndex &);
    virtual void setCalculateProperties(const QModelIndex &);
    virtual void preparePrintValues(QMap<QString, QVariant>*);     // Готовит значения для печати
};

#endif // ESSENCE_H
