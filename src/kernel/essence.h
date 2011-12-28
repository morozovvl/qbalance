#ifndef ESSENCE_H
#define ESSENCE_H

#define REPORT_DIR      "./reports/"
#define SCRIPT_DIR      "./scripts/"
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
    Q_INVOKABLE virtual qulonglong      getId(int row = -1);
    Q_INVOKABLE virtual QString         getName(int row = -1);
    virtual bool                        setData(const QModelIndex &, const QVariant &, int role = Qt::EditRole);
    virtual void                        setId(qulonglong);
    Q_INVOKABLE QString                 getCurrentFieldName() { return currentFieldName; }
    QString                             getIdFieldName() { return idFieldName; }
    Q_INVOKABLE virtual bool            isFieldExists(QString field) { return getFieldsList().contains(field); }
    Q_INVOKABLE virtual QVariant        getValue(QString, int row = -1);                 // Возвращает значение заданного поля в текущей записи
    Q_INVOKABLE virtual void            setValue(QString, QVariant, int row = -1);           // Устанавливает значение заданного поля в текущей записи
    Q_INVOKABLE virtual bool            add() { return false; }        // Добавление записи
    Q_INVOKABLE virtual bool            remove();                      // Удаление записи
    Q_INVOKABLE virtual void            view();
    virtual void                        print(QString);

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
    virtual void setScriptEngine();
    ScriptEngine* getScriptEngine();

// Прочие функции
    QString getPhotoPath();
    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();

signals:
    void showError(const QString &);

protected:
    QString             formTitle;
    QString             idFieldName;
    QString             nameFieldName;
    QString             currentFieldName;                   // имя поля, в котором был вызван метод calculate()
    FormGrid*           form;
    QWidget*            parentForm;
    ScriptEngine*       scriptEngine;
    bool                lInsertable;
    bool                lDeleteable;
    bool                lViewable;
    bool                lUpdateable;
    bool                lPrintable;
    virtual void        setForm();
    void                initForm();
    virtual void        preparePrintValues(QMap<QString, QVariant>*);     // Готовит значения для печати
};

#endif // ESSENCE_H
