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


class TApplication;
//class FormGrid;

class Essence : public Table {
    Q_OBJECT
    Q_PROPERTY(bool         isFormSelected  READ isFormSelected)

public:
    Essence(QString name = "", QObject *parent = 0);
    ~Essence();

    Q_INVOKABLE virtual bool            add() = 0;                          // Добавление записи
    Q_INVOKABLE virtual bool            remove();                       // Удаление записи
    Q_INVOKABLE virtual void            view();                         // Просмотр записи
    virtual void                        print(QString);                 // Печать

// Функции для получения, сохранения данных модели
    Q_INVOKABLE virtual qulonglong      getId(int row = -1);
    Q_INVOKABLE virtual QString         getName(int row = -1);
    Q_INVOKABLE virtual void            setId(qulonglong);
    QString                             getIdFieldName() { return idFieldName; }
    Q_INVOKABLE virtual bool            isFieldExists(QString field) { return getFieldsList().contains(field); }
    Q_INVOKABLE virtual QVariant        getValue(QString, int row = -1);                 // Возвращает значение заданного поля в текущей записи
    Q_INVOKABLE virtual void            setValue(QString, QVariant, int row = -1);           // Устанавливает значение заданного поля в текущей записи
    void                                setDoSubmit(bool submit) { doSubmit = submit; }

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
    Q_INVOKABLE virtual QWidget* getFormWidget();
    Q_INVOKABLE void setPhotoEnabled(bool enabled) { photoEnabled = enabled; }
    Q_INVOKABLE void setPhotoPath(QString path) { photoPath = path; }
    Q_INVOKABLE void setPhotoIdField(QString field) { photoIdField = field; }
    Q_INVOKABLE void setPhotoNameField(QString field) { photoNameField = field; }
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
    void setScriptEngineEnabled(bool enabled) { scriptEngineEnabled = enabled; }

// Функции для обеспечения работы скриптов
    virtual bool calculate(const QModelIndex &);
    virtual void setScriptEngine();
    ScriptEngine* getScriptEngine();
    void setOldValue(QString field, QVariant value) { oldValues.insert(field, value); }
    Q_INVOKABLE virtual QVariant getOldValue(QString field) { return oldValues.value(field); }
    Q_INVOKABLE virtual QVariant getOldValue() { return getOldValue(getCurrentFieldName()); }


// Скриптовые события
    void initFormEvent();
    void beforeShowFormEvent();
    void afterHideFormEvent();
    void closeFormEvent();
    QString preparePictureUrl();

// Прочие функции
    QString getPhotoFile();
    Q_INVOKABLE virtual bool open();
    Q_INVOKABLE virtual void close();
    void                initForm();
    static void         saveFile(QString, QByteArray*);
    static bool         getFile(QString, QString, FileType);
    void                saveOldValues();

signals:
    void                showError(const QString &);
    void                photoLoaded();



protected:
    QString             formTitle;
    QString             idFieldName;
    QString             nameFieldName;
    FormGrid*           form;
    QWidget*            parentForm;
    ScriptEngine*       scriptEngine;
    QString             scriptFileName;                     // Имя файла со скриптами
    QSqlQuery           preparedSelectCurrentRow;           // Содержит подготовленный запрос для обновления текущей строки при вычислениях
    bool                lInsertable;
    bool                lDeleteable;
    bool                lViewable;
    bool                lUpdateable;
    bool                lPrintable;
    virtual void        setForm();
    virtual void        preparePrintValues(ReportScriptEngine*);     // Готовит значения для печати
    virtual void        prepareSelectCurrentRowCommand();
    virtual void        selectCurrentRow();

private:
    bool                scriptEngineEnabled;
//    QVariant            oldValue;
    QString             photoPath;
    QString             photoIdField;
    QString             photoNameField;
    bool                photoEnabled;
    bool                doSubmit;
    QMap<QString, QVariant>             oldValues;

    QMap<QString, QString>  urls;                               // URL картинок в интернете и их локальные идентификаторы
    QNetworkAccessManager*      m_networkAccessManager;
    QNetworkRequest*    m_request;
    static qulonglong          calculateCRC32(QByteArray*);


private slots:
    void replyFinished(QNetworkReply*);

};

#endif // ESSENCE_H
