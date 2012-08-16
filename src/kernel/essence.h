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

#ifndef ESSENCE_H
#define ESSENCE_H

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
#include "../engine/reportscriptengine.h"
#include "../gui/dialog.h"


class TApplication;
class FormGrid;

class Essence : public Table {
    Q_OBJECT

public:
    Essence(QString name = "", QObject *parent = 0);
    ~Essence();

    Q_INVOKABLE virtual bool            add();                          // Добавление записи
    Q_INVOKABLE virtual bool            remove();                       // Удаление записи
    Q_INVOKABLE virtual void            view();                         // Просмотр записи
    virtual void                        print(QString);                 // Печать
    virtual void                        query(QString filter = "");

// Функции для получения, сохранения данных модели
    Q_INVOKABLE virtual qulonglong      getId(int row = -1);
    Q_INVOKABLE virtual QString         getName(int row = -1);
    Q_INVOKABLE virtual void            setId(qulonglong);
    Q_INVOKABLE QString                 getCurrentFieldName() { return currentFieldName; }
    QString                             getIdFieldName() { return idFieldName; }
    Q_INVOKABLE virtual bool            isFieldExists(QString field) { return getFieldsList().contains(field); }
    Q_INVOKABLE virtual QVariant        getValue(QString, int row = -1);                 // Возвращает значение заданного поля в текущей записи
    Q_INVOKABLE virtual void            setValue(QString, QVariant, int row = -1);           // Устанавливает значение заданного поля в текущей записи

// Функции для работы с модулем GUI
    virtual FormGrid* getForm() { return form; }
    virtual void cmdOk();                       // Обработка нажатий кнопок "Ok"
    virtual void cmdCancel();                   // и "Cancel"
    Q_INVOKABLE virtual bool isFormSelected();
    Q_INVOKABLE virtual int exec();                 // Показать форму в модальном режиме
    Q_INVOKABLE virtual void show();                // Показать форму в немодальном режиме
    Q_INVOKABLE virtual void hide();                // Скрыть форму
    Q_INVOKABLE void setFormTitle(QString);         // Установить заголовок формы
    Q_INVOKABLE QString getFormTitle();             // прочитать заголовок формы
    Q_INVOKABLE virtual Dialog* getFormWidget();
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
    void setOldValue(QVariant value) { oldValue = value; }
    Q_INVOKABLE virtual QVariant getOldValue() { return oldValue; }

// Прочие функции
    QString getPhotoPath();
    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();
    void                initForm();

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
    virtual void        preparePrintValues(ReportScriptEngine*);     // Готовит значения для печати
private:
    QVariant            oldValue;
};

#endif // ESSENCE_H
