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

#include <QtCore/QDebug>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtSql/QSqlTableModel>
#include <QtCore/QProcess>
#include <QtCore/QPointer>

#include <QtXml/QDomNode>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtGui/QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkReply>
#include "../kernel/table.h"
#include "../engine/scriptengine.h"
#include "../engine/documentscriptengine.h"
#include "../gui/formgrid.h"
#include "../gui/tableview.h"

class TApplication;

struct urlId {
    QString     id;                 // скачать файл с таким ID
    QString     copyTo;             // скопировать его в файл
};


class Essence : public Table {
    Q_OBJECT

public:
    Essence(QString name = "", QObject *parent = 0);
    ~Essence();

    Q_INVOKABLE virtual bool            open();
    Q_INVOKABLE virtual void            close();
    void                                initForm();
    Q_INVOKABLE virtual bool            add() = 0;                      // Добавление записи
    Q_INVOKABLE virtual bool            remove(bool = false);     // Удаление записи
    Q_INVOKABLE virtual void            view();                         // Просмотр записи
    virtual void                        print(QString, bool = false);                 // Печать
    virtual void                        load();

// Функции для получения, сохранения данных модели
    Q_INVOKABLE virtual qulonglong      getId(int row = -1);
    Q_INVOKABLE virtual QString         getName(int row = -1);
    Q_INVOKABLE virtual void            setId(qulonglong);
    Q_INVOKABLE virtual int             locateId(qulonglong);            // Возвращает номер строки с заданным полем КОД
    Q_INVOKABLE virtual int             locateValue(QString, QVariant);  // Возвращает номер строки с заданным значение поля
    Q_INVOKABLE virtual bool            isFieldExists(QString field) { return getFieldsList().contains(field); }
    Q_INVOKABLE virtual QVariant        getValue(QString, int row = -1);                 // Возвращает значение заданного поля в текущей записи
    Q_INVOKABLE virtual QVariant        getOldValue(QString field);
    Q_INVOKABLE virtual QVariant        getOldValue();
    Q_INVOKABLE virtual void            setValue(QString, QVariant, int row = -1);           // Устанавливает значение заданного поля в текущей записи
    Q_INVOKABLE void                    setDoSubmit(bool submit) { doSubmit = submit; }
    Q_INVOKABLE void                    setFilter(const QString &filter) { defaultFilter = filter; tableModel->setFilter(filter); }
    virtual void query(QString = "", bool = false);
    Q_INVOKABLE virtual void            setOrderClause(QString = "") { ; }
    Q_INVOKABLE int                     getRowCount() { return tableModel != 0 ? tableModel->rowCount() : 0; }
    Q_INVOKABLE int                     rowCount() { return getRowCount(); }


// Функции для работы с модулем GUI
    Q_INVOKABLE FormGrid* getForm() { return form; }
    Q_INVOKABLE TableView* getGrdTable() { return grdTable; }
    void setGrdTable(TableView* gt);
    Q_INVOKABLE virtual void cmdOk();                       // Обработка нажатий кнопок "Ok"
    Q_INVOKABLE virtual void cmdCancel();                   // и "Cancel"
    Q_INVOKABLE virtual bool isFormSelected();
    Q_INVOKABLE virtual int exec();                 // Показать форму в модальном режиме
    Q_INVOKABLE virtual void show();                // Показать форму в немодальном режиме
    Q_INVOKABLE virtual void hide();                // Скрыть форму
    Q_INVOKABLE void setFormTitle(QString);         // Установить заголовок формы
    Q_INVOKABLE QString getFormTitle();             // прочитать заголовок формы
    Q_INVOKABLE virtual Dialog* getFormWidget();
    Q_INVOKABLE void setPhotoEnabled(bool enabled) { photoEnabled = enabled; }
    Q_INVOKABLE bool isPhotoEnabled() { return photoEnabled; }
    Q_INVOKABLE virtual void setPhotoPath(QString path) { photoPath = path; }
    Q_INVOKABLE QString getPhotoPath();
    Q_INVOKABLE void setPhotoIdField(QString field) { photoIdField = field; }
    Q_INVOKABLE void setPhotoNameField(QString field) { photoNameField = field; }
    Q_INVOKABLE QString getPhotoNameField() { return photoNameField; }
    Q_INVOKABLE virtual void removePhoto(QString = "");
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
    Q_INVOKABLE void hideAllGridSections() { grdTable->hideAllGridSections(); }
    Q_INVOKABLE void hideGridSection(QString columnName)  { grdTable->hideGridSection(columnName); }
    Q_INVOKABLE void showGridSection(QString columnName) { grdTable->showGridSection(columnName); }
    Q_INVOKABLE void showAllGridSections() { grdTable->showAllGridSections(); }
    Q_INVOKABLE virtual void setForm(QString = "") { ; }
    Q_INVOKABLE bool isDefaultForm() { return form->isDefaultForm(); }
    Q_INVOKABLE bool isFormVisible() { return form != 0 ? form->isVisible() : false; }


// Функции для обеспечения работы скриптов
    virtual void        setScriptEngine();
    ScriptEngine*       getScriptEngine();
    void                setScriptEngineEnabled(bool enabled) { scriptEngineEnabled = enabled; }
    virtual void        evaluateEngine();
    virtual bool        calculate(bool = true);
    virtual void        saveOldValues();                // Сохраняет значения полей текущей строки перед вычислениями
    virtual void        restoreOldValues();
    Q_INVOKABLE virtual QScriptValue evaluateScript(QString);


// Скриптовые события
    void                initFormEvent();
    void                beforeShowFormEvent(Form *);
    void                afterShowFormEvent(Form *);
    void                beforeHideFormEvent(Form *);
    void                afterHideFormEvent(Form *);
    void                closeFormEvent(Form *);
    QString             preparePictureUrl();
    virtual void        afterRowChanged();
    virtual void        beforeRowChanged();

// Прочие функции
    Q_INVOKABLE         virtual QString getPhotoFile(QString copyTo = "");
    Q_INVOKABLE         QString getLocalPhotoFile(QString = "");
    static bool         getFile(QString, QString, FileType);
    virtual void        barCodeReaded(QString);    // прочитана строка со сканера штрих-кода
    Q_INVOKABLE virtual void        updateCurrentRow();
    QModelIndex         getCurrentIndex();
    void setCurrentIndex(QModelIndex);
    Q_INVOKABLE QString         getCurrentFieldName() { return tableModel->getFieldName(getCurrentColumn()).toUpper(); }
    Q_INVOKABLE virtual int     getCurrentRow() { return getCurrentIndex().row(); }
    Q_INVOKABLE virtual int     getCurrentColumn() { return getCurrentIndex().column(); }
    Q_INVOKABLE virtual void    setCurrentRow(int row) { if (grdTable != 0) grdTable->selectRow(row); }
    Dictionaries* getDictionaries() { return dictionaries; }
    void setDictionaries(Dictionaries* dicts) { dictionaries = dicts; }     // Устанавливает указатель на список справочников,
    bool    isLoading() { return loading; }
    Q_INVOKABLE void    clearPrintValues();
    Q_INVOKABLE void    appendPrintValue(QString name, QVariant value) { reportScriptEngine->getReportContext()->setValue(name, value); }
    Q_INVOKABLE void    appendPrintValues(QString str, QSqlQuery* query) { reportScriptEngine->getReportContext()->appendPrintValues(str, query); }
    Q_INVOKABLE QVariant getPrintValue(QString name) { return reportScriptEngine->getReportContext()->getValue(name); }
    bool                isDocument() { return lIsDocument; }
    Q_INVOKABLE void    showPhoto() { form->showPhoto(); }

signals:
    void                photoLoaded();

public slots:
    void                cardCodeReaded(QString);


protected:
    bool                scriptEngineEnabled;
    QString             formTitle;
    QString             idFieldName;
    QString             nameFieldName;
    FormGrid*           form;
    Dictionaries*       dictionaries;
    TableView*          grdTable;
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
    bool                doSubmit;
    bool                isCurrentCalculate;                     // Переменная, не позволяющая во время работы функции Calculate, войти в нее второй раз
    bool                photoEnabled;
    QHash<QString, QVariant>             oldValues;              // Старые значения для текущей строки
    DocumentScriptEngine* reportScriptEngine;
    bool                lIsDocument;

    virtual void        preparePrintValues();                   // Готовит значения для печати
    virtual void        prepareSelectCurrentRowCommand();
    void                openScriptEngine();
    void                closeScriptEngine();
    bool                isDocumentLoading();


private:
    bool                photoPathVerified;
    QString             photoPath;
    QString             photoIdField;
    QString             photoNameField;
    bool                loading;            // Сейчас идет заполнение документа (справочника) из файла


    QHash<QString, urlId>  urls;                               // URL картинок в интернете и их локальные идентификаторы
    QNetworkAccessManager*  m_networkAccessManager;


private slots:
    void                replyFinished(QNetworkReply*);

};

#endif // ESSENCE_H
