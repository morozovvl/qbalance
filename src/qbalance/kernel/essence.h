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

#define TMP_DIR         "./tmp/"

#include <QDebug>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtSql/QSqlTableModel>
#include <QtCore/QProcess>

#include <QtXml/QDomNode>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtGui/QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "../kernel/table.h"
#include "../engine/scriptengine.h"
#include "../engine/reportscriptengine.h"
#include "../gui/formgrid.h"
#include "../gui/tableview.h"


class TApplication;
//class FormGrid;

class Essence : public Table {
    Q_OBJECT

public:
    Essence(QString name = "", QObject *parent = 0);
    ~Essence();

    Q_INVOKABLE virtual bool            open();
    Q_INVOKABLE virtual void            close();
    void                                initForm();
    Q_INVOKABLE virtual bool            add() = 0;                      // Добавление записи
    Q_INVOKABLE virtual bool            remove();                       // Удаление записи
    Q_INVOKABLE virtual void            view();                         // Просмотр записи
    virtual void                        print(QString);                 // Печать

// Функции для получения, сохранения данных модели
    Q_INVOKABLE virtual qulonglong      getId(int row = -1);
    Q_INVOKABLE virtual QString         getName(int row = -1);
    Q_INVOKABLE virtual void            setId(qulonglong);
    Q_INVOKABLE virtual bool            isFieldExists(QString field) { return getFieldsList().contains(field); }
    Q_INVOKABLE virtual QVariant        getValue(QString, int row = -1);                 // Возвращает значение заданного поля в текущей записи
    Q_INVOKABLE virtual QVariant        getOldValue(QString field);
    Q_INVOKABLE virtual QVariant        getOldValue();
    Q_INVOKABLE virtual void            setValue(QString, QVariant, int row = -1);           // Устанавливает значение заданного поля в текущей записи
    void                                setDoSubmit(bool submit) { doSubmit = submit; }
    bool                                getDoSubmit() { return doSubmit; }
    Q_INVOKABLE void                    setFilter(const QString &filter) { defaultFilter = filter; tableModel->setFilter(filter); }
    virtual void query(QString = "");
    virtual void                        setOrderClause() { ; }


// Функции для работы с модулем GUI
    virtual FormGrid* getForm();
    virtual void cmdOk();                       // Обработка нажатий кнопок "Ok"
    virtual void cmdCancel();                   // и "Cancel"
    Q_INVOKABLE virtual bool isFormSelected();
    Q_INVOKABLE virtual int exec();                 // Показать форму в модальном режиме
    Q_INVOKABLE virtual void show();                // Показать форму в немодальном режиме
    Q_INVOKABLE virtual void hide();                // Скрыть форму
    Q_INVOKABLE void setFormTitle(QString);         // Установить заголовок формы
    Q_INVOKABLE QString getFormTitle();             // прочитать заголовок формы
    Q_INVOKABLE virtual Dialog* getFormWidget();
    Q_INVOKABLE void setPhotoEnabled(bool enabled) { photoEnabled = enabled; }
    Q_INVOKABLE void setPhotoPath(QString path) { photoPath = path; }
    QString getPhotoPath();
    Q_INVOKABLE void setPhotoIdField(QString field) { photoIdField = field; }
    Q_INVOKABLE void setPhotoNameField(QString field) { photoNameField = field; }
    Q_INVOKABLE bool isInsertable() { return lInsertable; }         // Получить/установить ...
    Q_INVOKABLE bool isDeleteable() { return lDeleteable; }         // ... свойства отображения ...
    Q_INVOKABLE bool isViewable() { return lViewable; }             // ... кнопок на форме
    Q_INVOKABLE bool isUpdateable() { return lUpdateable; }
    Q_INVOKABLE bool isPrintable() { return lPrintable; }
    Q_INVOKABLE void setInsertable(bool b) { lInsertable = b; form->setButtonAdd(b); }
    Q_INVOKABLE void setDeleteable(bool b) { lDeleteable = b; form->setButtonDelete(b); }
    Q_INVOKABLE void setViewable(bool b) { lViewable = b; }
    Q_INVOKABLE void setUpdateable(bool b) { lUpdateable = b; }
    Q_INVOKABLE void setPrintable(bool b) { lPrintable = b; }
    Q_INVOKABLE virtual void setEnabled(bool);
    Q_INVOKABLE bool isEnabled() { return enabled; }
    Q_INVOKABLE void hideAllGridSections() { form->getGridTable()->hideAllGridSections(); }
    Q_INVOKABLE void hideGridSection(QString columnName)  { form->getGridTable()->hideGridSection(columnName); }
    Q_INVOKABLE void showGridSection(QString columnName) { form->getGridTable()->showGridSection(columnName); }
    Q_INVOKABLE void showAllGridSections() { form->getGridTable()->showAllGridSections(); }
    Q_INVOKABLE virtual void setForm(QString = "");


// Функции для обеспечения работы скриптов
    virtual void        setScriptEngine();
    ScriptEngine*       getScriptEngine();
    void                setScriptEngineEnabled(bool enabled) { scriptEngineEnabled = enabled; }
    void                evaluateEngine();
    virtual bool        calculate(const QModelIndex &);
    virtual void        saveOldValues();                // Сохраняет значения полей текущей строки перед вычислениями
    virtual void        restoreOldValues();


// Скриптовые события
    void                initFormEvent();
    void                beforeShowFormEvent();
    void                afterShowFormEvent();
    void                beforeHideFormEvent();
    void                afterHideFormEvent();
    void                closeFormEvent();
    QString             preparePictureUrl();

// Прочие функции
    QString             getPhotoFile();
    static void         saveFile(QString, QByteArray*);
    static bool         getFile(QString, QString, FileType);

signals:
    void                photoLoaded();



protected:
    bool                scriptEngineEnabled;
    QString             formTitle;
    QString             idFieldName;
    QString             nameFieldName;
    FormGrid*           form;
    QWidget*            parentForm;
    ScriptEngine*       scriptEngine;
    QString             scriptFileName;                     // Имя файла со скриптами
    QSqlQuery           preparedSelectCurrentRow;           // Содержит подготовленный запрос для обновления текущей строки при вычислениях
    QString             defaultFilter;
    bool                lInsertable;
    bool                lDeleteable;
    bool                lViewable;
    bool                lUpdateable;
    bool                lPrintable;
    bool                isDictionary;
    bool                enabled;
    QMap<QString, QVariant>             oldValues;              // Старые значения для текущей строки
    virtual void        preparePrintValues(ReportScriptEngine*);     // Готовит значения для печати
    virtual void        prepareSelectCurrentRowCommand();
    virtual void        updateCurrentRow();

private:
    QString             photoPath;
    QString             photoIdField;
    QString             photoNameField;
    bool                photoEnabled;
    bool                doSubmit;
    QWidget*            activeWidget;

    QMap<QString, QString>  urls;                               // URL картинок в интернете и их локальные идентификаторы
    QNetworkAccessManager*  m_networkAccessManager;
    QNetworkRequest*        m_request;
    static qulonglong       calculateCRC32(QByteArray*);


private slots:
    void                replyFinished(QNetworkReply*);

};

#endif // ESSENCE_H
