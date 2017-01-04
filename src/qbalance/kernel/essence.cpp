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

#include <QtCore/QVariant>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QtSql/QSqlField>
#include <QtCore/QHash>
#include <QtCore/QDir>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtGui/QMessageBox>
#include <QtGui/QMenu>
#include <QtCore/QFile>
#include <QtCore/QTemporaryFile>
#include <QtCore/QDebug>
#include <QtGui/QImage>
//#include <boost/crc.hpp>
#include "essence.h"
#include "../kernel/app.h"
#include "../kernel/document.h"
#include "../kernel/dictionaries.h"
#include "../gui/form.h"
#include "../gui/formgridsearch.h"
#include "../gui/mainwindow.h"
#include "../gui/tableview.h"
#include "../gui/dialog.h"
#include "../report/reportengine.h"
#include "../report/ooreportengine.h"
//#include "../report/oounoreportengine.h"
#include "../report/ooxmlreportengine.h"
#include "../engine/reportcontext.h"
#include "../engine/documentscriptengine.h"
#include "../storage/dbfactory.h"
//#include "../mpreal.h"
//#include "../../fixedpoint/fixed_class.h"
//#include "../../fixedpoint/fixed_func.h"
//#include "../../fpml/fixed_point.h"
#include "../fixed.h"



Essence::Essence(QString name, QObject *parent): Table(name, parent)
{
}


Essence::~Essence() {
    this->disconnect();
}


void Essence::postInitialize(QString name, QObject* parent)
{
    Table::postInitialize(name, parent);

    form = 0;
    scriptEngine = 0;
    parentForm = app->getMainWindow()->centralWidget();
    formTitle   = "";
    lInsertable = false;
    lDeleteable = false;
    lViewable   = false;
    lUpdateable = false;
    lPrintable  = false;
    isDictionary = true;
    enabled     = true;
    isCurrentCalculate = false;
    sortedTable = true;
    idFieldName = db->getObjectName("код");
    nameFieldName = db->getObjectName("имя");
    scriptFileName =  tagName;
    if (tagName.size() > 0)
        scriptFileName += ".qs";
    scriptEngineEnabled = true;                 // По умолчанию разрешена загрузка скриптового движка
    photoPath = "";
    photoPathVerified = false;
    photoIdField = "";
    photoEnabled = false;
    m_networkAccessManager = 0;
    doSubmit = false;                           // По умолчанию не обновлять записи автоматически
    defaultFilter = "";
    grdTable = 0;
    dictionaries = 0;
    loading = false;
    reportScriptEngine = 0;
    lIsDocument = false;
    cardReaderEnabled = false;
}


bool Essence::isFieldExists(QString field)
{
    return getFieldsList().contains(field);
}


void Essence::setDoSubmit(bool submit)
{
    doSubmit = submit;
}


void Essence::setFilter(const QString &filter)
{
    defaultFilter = filter;
    tableModel->setFilter(filter);
}


int Essence::getRowCount()
{
    return tableModel != 0 ? tableModel->rowCount() : 0;
}


int Essence::rowCount()
{
    return getRowCount();
}


FormGrid* Essence::getForm()
{
    return form;
}


TableView* Essence::getGrdTable()
{
    return grdTable;
}


void Essence::setPhotoEnabled(bool enabled)
{
    photoEnabled = enabled;
}


bool Essence::isPhotoEnabled()
{
    return photoEnabled;
}


void Essence::setPhotoPath(QString path)
{
    photoPath = path;
}


void Essence::setPhotoIdField(QString field)
{
    photoIdField = field;
}


void Essence::setPhotoNameField(QString field)
{
    photoNameField = field;
}


QString Essence::getPhotoNameField()
{
    return photoNameField;
}


bool Essence::isInsertable()
{
    return lInsertable;
}         // Получить/установить ...


bool Essence::isDeleteable()
{
    return lDeleteable;
}         // ... свойства отображения ...


bool Essence::isViewable()
{
    return lViewable;
}             // ... кнопок на форме


bool Essence::isUpdateable()
{
    return lUpdateable;
}


bool Essence::isPrintable()
{
    return lPrintable;
}


void Essence::setViewable(bool b)
{
    lViewable = b;
}


void Essence::setUpdateable(bool b)
{
    lUpdateable = b;
}


void Essence::setPrintable(bool b)
{
    lPrintable = b;
}


bool Essence::isEnabled()
{
    return enabled;
}


void Essence::hideAllGridSections()
{
    grdTable->hideAllGridSections();
}


void Essence::hideGridSection(QString columnName)
{
    grdTable->hideGridSection(columnName);
}


void Essence::showGridSection(QString columnName)
{
    grdTable->showGridSection(columnName);
}


void Essence::showAllGridSections()
{
    grdTable->showAllGridSections();
}


bool Essence::isDefaultForm()
{
    return form->isDefaultForm();
}


bool Essence::isFormVisible()
{
    return form != 0 ? form->isVisible() : false;
}


bool Essence::getIsDictionary()
{
    return isDictionary;
}


void Essence::setScriptEngineEnabled(bool enabled)
{
    scriptEngineEnabled = enabled;
}


QString Essence::getCurrentFieldName()
{
    return tableModel->getFieldName(getCurrentColumn()).toUpper();
}


int Essence::getCurrentRow()
{
    return getCurrentIndex().row();
}


int Essence::getCurrentColumn()
{
    return getCurrentIndex().column();
}


void Essence::setCurrentRow(int row)
{
    if (grdTable != 0) grdTable->selectRow(row);
}


Dictionaries* Essence::getDictionaries()
{
    return dictionaries;
}


void Essence::setDictionaries(Dictionaries* dicts)
{
    dictionaries = dicts;
}     // Устанавливает указатель на список справочников


bool Essence::isLoading()
{
    return loading;
}


void Essence::appendPrintValue(QString name, QVariant value)
{
    if (reportScriptEngine != 0)
    {
        int currentRow = reportScriptEngine->getReportContext()->getCurrentRow();
        if (currentRow > 0)
            reportScriptEngine->getReportContext()->setValue(QString("таблица.%1").arg(name).toLower(), value, currentRow);
        else
            reportScriptEngine->getReportContext()->setValue(name, value);
    }
}


void Essence::appendPrintValues(QString str, QSqlQuery* query)
{
    if (reportScriptEngine != 0)
        reportScriptEngine->getReportContext()->appendPrintValues(str, query);
}


QVariant Essence::getPrintValue(QString name)
{
    QVariant result;
    if (reportScriptEngine != 0)
        result = reportScriptEngine->getReportContext()->getValue(name);
    return result;
}


bool Essence::isDocument()
{
    return lIsDocument;
}


void Essence::showPhoto()
{
    form->showPhoto();
}


void Essence::setInsertable(bool b)
{
    lInsertable = b; form->setButtonAdd(b);
}


void Essence::setDeleteable(bool b)
{
    lDeleteable = b;
    form->setButtonDelete(b);
}


Dialog* Essence::getFormWidget()
{
    if (!opened)
    {
        open();
    }
    return (form != 0 ? form->getFormWidget() : 0);
}

bool Essence::isVisible()
{
    return form->isVisible();
}


bool Essence::calculate(bool)
{
    if (scriptEngineEnabled && scriptEngine != 0)
    {
        scriptEngine->eventCalcTable();
        scriptEngine->eventAfterCalculate();
        if (scriptEngine->getErrorMessage().size() > 0)
        {
            app->showError(scriptEngine->getErrorMessage());
            scriptEngine->setErrorMessage("");
        }
        if (!scriptEngine->getScriptResult())
        {
            isCurrentCalculate = false;
            return false;
        }
    }
    return true;
}


QScriptValue Essence::evaluateScript(QString script)
{
    QScriptValue result;
    if (scriptEngine != 0)
    {
        QRegExp rx("^\\D+.*\\(.*\\)$");
        QRegExp argrx("\\(.*\\)$");

        if (script.contains(rx))
        {
            QString sargs = script.mid(script.indexOf(argrx));
            script = script.remove(argrx);
            sargs = sargs.remove("(").remove(")");

            QScriptValueList args;
            args << QScriptValue(sargs);
            result = scriptEngine->globalObject().property(script).call(QScriptValue(), args);
        }
        else
            result = scriptEngine->globalObject().property(script);
        if (scriptEngine->hasUncaughtException())
        {   // Если в скриптах произошла ошибка
            scriptEngine->showScriptError(script);
        }
    }
    return result;
}


QVariant Essence::getValue(QString n, int row)
{
    QVariant result;
    if (n.size() > 0 && tableModel->rowCount() > 0)
    {
        QString name = n.toUpper();
        QSqlRecord record = tableModel->record();
        if (record.contains(name))
        {
            if (row < 0)
                row = getCurrentRow();
            result = tableModel->data(tableModel->index(row, tableModel->fieldIndex(name)));
            QVariant::Type type = record.field(name).type();
            if (type == QVariant::Double)
            {
                // Округлим значение числового поля до точности как и в БД
                int precision = 0;
                for (int i = 0; i < columnsProperties.count(); i++)
                {
                    if (columnsProperties.at(i).column == n)
                    {
                        precision = columnsProperties.at(i).precision;
                        break;
                    }
                }
                result = QString().setNum(result.toDouble(), 'f', precision).toDouble();
            }
            else if (type == QVariant::Int)
            {
                result = result.toInt();
            }
        }
        else
            app->showError(QObject::trUtf8("Не существует колонки ") + n);
    }
    return result;
}


void Essence::setValue(QString n, QVariant value, int row)
{
    n = n.toUpper();
    int fieldColumn = tableModel->fieldIndex(n);
    if (fieldColumn >= 0)
    {
        if (row < 0)
            row = getCurrentRow();

        QModelIndex index, oldIndex;
        oldIndex = getCurrentIndex();
        index = tableModel->index(row, fieldColumn);

        for (int i = 0; i < columnsProperties.count(); i++)
        {
            if (columnsProperties.at(i).column == n)
            {
                if (columnsProperties.at(i).type.toUpper() == "NUMERIC" && (value.toDouble() - value.toInt()) != 0)
                {

                    // Вся эта фигня ...
                    int precision = columnsProperties.at(i).precision;
                    double val = value.toDouble();
                    if (val > 0)
                        val += 0.01/qPow(10, precision);
                    else if (val < 0)
                        val -= 0.01/qPow(10, precision);
                    QString str = QString().setNum(val, 'f', precision);
                    // это бл... округление до заданного знака после запятой

                    tableModel->setData(index, str.toDouble());
                }
                else
                    tableModel->setData(index, value);  // QSqlQuery::value: not positioned on a valid record
                break;
            }
        }

        tableModel->submit(index);

        if (doSubmit)
            db->execCommands();

        setCurrentIndex(oldIndex);
    }
    else
        app->showError(QObject::trUtf8("Не существует колонки ") + n);
}


qulonglong Essence::getId(int row)
{
    if (row < 0)
        row = getCurrentRow();
    return getValue(idFieldName, row).toULongLong();
}


int Essence::locateId(qulonglong id)
{
    for (int i = 0; i < tableModel->rowCount(); i++)
    {
        if (getId(i) == id)
            return i;
    }
    return -1;
}


int Essence::locateValue(QString fieldName, QVariant value)
{
    for (int i = 0; i < tableModel->rowCount(); i++)
    {
        if (getValue(fieldName, i) == value)
            return i;
    }
    return -1;
}


QString Essence::getName(int row)
{
    if (row >= 0)
        return getValue(nameFieldName, row).toString().trimmed();
    int r = getCurrentIndex().isValid() ? getCurrentRow() : 0;
    return getValue(nameFieldName, r).toString().trimmed();
}


void Essence::setId(qulonglong id)
{
    bool enabled = photoEnabled;
    photoEnabled = false;
    if (getValue(idFieldName) != id)
    {
        // На время отключим обновление(показ) фотографии
        query(QString("\"%1\".\"%2\"=%3").arg(tableName).arg(idFieldName).arg(id), true);
    }
    if (grdTable != 0)
    {
        grdTable->selectRow(0);
        grdTable->setCurrentIndex(grdTable->currentIndex().sibling(0, grdTable->currentIndex().column()));
    }
    photoEnabled = enabled;
}


void Essence::query(QString filter, bool)
{
    int row = getCurrentRow();
    if (filter.size() > 0 && defaultFilter.size() > 0)
    {
        Table::query(filter + " AND " + defaultFilter);
    }
    else if (defaultFilter.size() > 0)
    {
        Table::query(defaultFilter);
    }
    else
        Table::query(filter);
    setCurrentRow(row);
 }


QString Essence::getPhotoPath()
{
    QString path;
    // Попробуем получить локальный путь к фотографии
    if (isDictionary && photoPath.size() == 0 && !photoPathVerified)
    {
        // Если путь, откуда нужно брать фотографии не установлен, то установим его по умолчанию для данного справочника
        path = db->getDictionaryPhotoPath(tableName);
        if (path.size() == 0)
            photoEnabled = false;
        photoPath = path;
        photoPathVerified = true;           // Чтоб больше не спрашивала
    }
    else
    {
        path = photoPath;
    }
    return path;
}


QString Essence::getLocalPhotoFile(QString path)
{
    QString result;
    QString idValue = getValue(photoIdField).toString().trimmed();
    if (idValue.size() > 0 && idValue != "0")
    {
        if (path.size() == 0)
            result = app->getPhotosPath(getPhotoPath());
        else
            result = path;
        result += "/" + idValue + ".jpg";
    }
    return result;
}


QString Essence::getPhotoFile(QString copyTo)
{
    QString idValue;    // Значение идентификатора фотографии
    QString file;       // Полное имя файла с фотографией
    QString localFile;  // Локальный путь к фотографии
    QString pictureUrl;
    bool phEnabled = photoEnabled;
    if (phEnabled || copyTo.size() > 0)
    {
        // Сначала получим имя поля из которого будем брать значение идентификатора
        if (photoIdField.size() == 0 && (isDictionary || app->getConfigValue("GET_PICTURE_FROM_SERVER_IN_DOCUMENT").toBool()))
        {
            // Если имя поля, из которого нужно брать идентификатор фотографии не установлено, то будем считать идентификатором код позиции
            photoIdField = db->getObjectName("код");
        }

        // Теперь получим значение идентификатора
        if (tableModel->rowCount() > 0 && photoIdField.size() > 0)
        {
            pictureUrl = preparePictureUrl();
            localFile = getLocalPhotoFile(getPhotoPath());       // Запомним локальный путь к фотографии на случай обращения к серверу за фотографией
            idValue = getValue(photoIdField).toString().trimmed();
            if (localFile.size() > 0 && photoEnabled)
            {
                file = getLocalPhotoFile();
                if (isDictionary)
                {
                    if (!QFile(file).exists() && phEnabled)
                    {   // Локальный файл с фотографией не найден, попробуем получить фотографию с нашего сервера. Будем делать это только для справочника, а не для документа
                        // Мы знаем, под каким именем искать фотографию на нашем сервере, то попробуем обратиться к нему за фотографией
                        if (db->getFileCheckSum(localFile, PictureFileType, true) != 0)
                        {
//                        app->showMessageOnStatusBar(tr("Запущена загрузка с сервера фотографии с кодом ") + QString("%1").arg(idValue), 3000);
                            QByteArray picture = db->getFile(localFile, PictureFileType, true); // Получить файл с картинкой из расширенной базы
                            if (picture.size() > 0)
                            {   // Если удалось получить какую-то фотографию
                                app->saveFile(file, &picture);
                                if (copyTo.size() > 0)
                                    app->saveFileToServer(app->getPhotosPath(copyTo), file, PictureFileType, true);   // Если указано, что фотографию нужно скопировать, то скопируем ее
                            }
                        }
                        if (!QFile(file).exists())
                        {   // Фотография не найдена на сервере, попробуем получить фотографию из Интернета
                            file = pictureUrl;
                            // Если в скриптах указано, откуда брать фотографию
                            if (file.left(4) == "http" && photoPath.size() > 0)  // Имя файла - это адрес в интернете, и указано, куда этот файл будет сохраняться
                            {
                                QUrl url(file);
                                if (url.isValid())
                                {
                                    if (urls.count() <= 1000)
                                    {
                                        // Если сетевой менеджер еще не подключен, то подключим его
                                        if (m_networkAccessManager == 0)
                                        {   // Вызывается только один раз, по необходимости загрузить фотографию
                                            m_networkAccessManager = new QNetworkAccessManager(this);
                                            connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
                                        }
                                        if (m_networkAccessManager != 0)
                                        {
                                            urlId v = {idValue, copyTo};
                                            urls.insert(QString("%1:%2%3").arg(url.host()).arg(url.port(80)).arg(url.path()), v);             // Запомним URL картинки и его локальный код
                                            QNetworkRequest m_request(url);
                                            QNetworkReply* reply = m_networkAccessManager->get(m_request);   // Запустим скачивание картинки
                                            if (reply->error() != QNetworkReply::NoError)
                                               app->showMessageOnStatusBar(reply->errorString(), 3000);
                                        }
                                    }
                                    else
                                        app->showMessageOnStatusBar(tr("Очередь на загрузку фотографий из Интернета превысила 1000 наименований."), 3000);
                                }
                                else
                                    file = "";
                            }
                        }
                    }
                    else
                    {   // Локальный файл с фотографией найден. Проверим, имеется ли он на сервере в расширенной базе и если что, то сохраним его там
                        app->saveFileToServer(file, localFile, PictureFileType, true);
                        if (copyTo.size() > 0)
                        {
                            app->saveFileToServer(file, copyTo, PictureFileType, true);   // Если указано, что фотографию нужно скопировать, то скопируем ее
                        }
                    }
                }
            }
        }
    }
    return file;
}


void Essence::removePhoto(QString photo)
{
    QString photoFile = (photo.size() == 0 ? getLocalPhotoFile() : photo);
    if (photoFile.size() > 0)
    {
        QString localFile = getLocalPhotoFile(getPhotoPath());       // Запомним локальный путь к фотографии на случай обращения к серверу за фотографией
        QFile file(photoFile);
        if (file.remove())
        {
            db->removeFile(localFile, PictureFileType, true);
        }
    }
}


void Essence::replyFinished(QNetworkReply* reply)
{
    QString url = QString("%1:%2%3").arg(reply->url().host()).arg(reply->url().port(80)).arg(reply->url().path());
    QString idValue = urls.value(url).id;
    QString copyTo = urls.value(url).copyTo;
    urls.remove(url);
    if (reply->error() == QNetworkReply::NoError)
    {
        // Данные с фотографией получены, запишем их в файл
        QString localFile = getPhotoPath() + "/" + idValue + ".jpg";
        QString file = app->getPhotosPath(localFile);
        QByteArray array = reply->readAll();
        if (array.size() > 0)
        {
            QImage picture;
            app->saveFile(file, &array);
            if (picture.load(file))
            {
                app->showMessageOnStatusBar(QString(tr("Загружена фотография с кодом %1. Осталось загрузить %2")).arg(idValue).arg(urls.size()), 3000);

                if (copyTo.size() > 0)
                {
                    db->copyFile(localFile, copyTo, true);
                }

                // Проверим, не нужно ли обновить фотографию
                if (idValue == getValue(photoIdField).toString().trimmed())
                {
                    emit photoLoaded();                 // Выведем фотографию на экран
                    if (scriptEngineEnabled && scriptEngine != 0)
                        scriptEngine->eventPhotoLoaded();
                }
            }
            else
            {
                removePhoto(file);
            }
        }
    }
    else
        app->showMessageOnStatusBar(QString(tr("Не удалось загрузить фотографию с кодом %1. Осталось загрузить %2")).arg(idValue).arg(urls.size()), 3000);

    reply->close();
    reply->deleteLater();
}


bool Essence::remove(bool noAsk)
{
    if (!noAsk)
    {
        if (app->getGUIFactory()->showYesNo(QObject::trUtf8("Удалить запись? Вы уверены?")) == QMessageBox::Yes)
        {
            return true;
        }
        return false;
    }
    else
        return true;
}


int Essence::exec()
{
    int result = 0;
    if (!opened)
        open();
    if (opened && form != 0)
    {
        beforeShowFormEvent(getForm());
        form->exec();
        afterShowFormEvent(getForm());
    }
    return result;
}


void Essence::show()
{
    if (!opened)
        open();
    if (opened && form != 0)
    {
        beforeShowFormEvent(getForm());
        form->show();
        afterShowFormEvent(getForm());
    }
}


void Essence::hide()
{
    if (opened && form != 0)
    {
        if (isFormVisible())
            beforeHideFormEvent(form);
        form->hide();
        afterHideFormEvent(form);
    }
}


void Essence::view()
{
    if (form != 0)
        form->getFormWidget()->setFocus(Qt::OtherFocusReason);
}


bool Essence::open()
{
    if (Table::open())
    {
        setOrderClause();
        if (!app->isScriptMode())       // Если мы работаем не в скриптовом режиме, то создадим форму для этой сущности
            initForm();
        openScriptEngine();
        return true;
    }
    return false;
}


void Essence::close()
{

    if (m_networkAccessManager != 0)
        delete m_networkAccessManager;

    closeScriptEngine();

    if (form != 0)
    {
        form->close();
        if (form->isDefaultForm())
        {
            delete form;
            form = 0;
        }
        else
            form->deleteLater();
    }

    Table::close();
}


void Essence::setGrdTable(TableView* gt)
{
    grdTable = gt;
    grdTable->setEssence(this);
}


void Essence::setScriptEngine()
{
    scriptEngine = new ScriptEngine(this);
}


void Essence::evaluateEngine()
{
    if (scriptEngineEnabled && scriptEngine != 0)
    {
        scriptEngineEnabled = false;
        if (scriptEngine->open(scriptFileName))
        {
            if (scriptEngine->evaluate())
            {
                scriptEngineEnabled = true;
            }
        }
    }
}


ScriptEngine* Essence::getScriptEngine()
{
    return scriptEngine;
}


void Essence::openScriptEngine()
{
//    if (scriptEngineEnabled && db->isFileExist(scriptFileName, ScriptFileType))
    if (scriptEngineEnabled && scriptFileName.size() > 0)
    {
        setScriptEngine();
        evaluateEngine();
        if (dictionaries != 0 && dictionaries->getDocument() != 0)          // Если этот справочник является частью документа
            scriptEngine->setIsDocumentScript(true);                                             // То обозначим контекст выполнения скриптов

        initFormEvent();
    }
}


void Essence::closeScriptEngine()
{
    closeFormEvent(form);
    if (scriptEngineEnabled && scriptEngine != 0)
    {
        scriptEngine->close();
        scriptEngine->deleteLater();        // НЕ ИЗМЕНЯТЬ. ЕСЛИ СДЕЛАТЬ ПО-ДРУГОМУ, ВОЗМОЖНА ОШИБКА СЕГМЕНТАЦИИ
    }
}


void Essence::setEnabled(bool en)
{
    QString disabledMessage = QObject::trUtf8(" - изменения запрещены");
    enabled = en;
    if (scriptEngineEnabled && scriptEngine != 0)
        scriptEngine->eventSetEnabled(en);
    if (enabled)
        setFormTitle(getFormTitle().remove(disabledMessage));
    else
    {
        if (!getFormTitle().contains(disabledMessage))
            setFormTitle(form->getFormWidget()->windowTitle().append(disabledMessage));
    }
}


QVariant Essence::getOldValue(QString field)
{
    return oldValues.value(field);
}


QVariant Essence::getOldValue()
{
    return getOldValue(getCurrentFieldName());
}


void Essence::initForm() {
    setForm();
    setFormTitle(formTitle);
}


void Essence::setFormTitle(QString title) {
    formTitle = title;
    if (form != 0)
        form->getFormWidget()->setWindowTitle(title);
}


QString Essence::getFormTitle()
{
    if (form != 0)
        return form->getFormWidget()->windowTitle();
    return QString();
}


bool Essence::isFormSelected()
{
    if (form != 0)
        return form->isFormSelected();
    return false;
}


void Essence::cmdOk()
{
}


void Essence::cmdCancel()
{
}


void Essence::load()
{
    loading = true;
    // На время загрузки запретим просмотр и загрузку фотографий
    bool photoEnabled = isPhotoEnabled();
    setPhotoEnabled(false);
    getScriptEngine()->eventImport(form);
    setPhotoEnabled(photoEnabled);
    loading = false;
}


void Essence::initFormEvent()
{
    if (scriptEngineEnabled && getScriptEngine() != 0)
        getScriptEngine()->eventInitForm(form);
}


void Essence::beforeShowFormEvent(Form* form)
{
    if (scriptEngineEnabled && getScriptEngine() != 0)
        getScriptEngine()->eventBeforeShowForm(form);
}


void Essence::afterShowFormEvent(Form* form)
{
    if (scriptEngineEnabled && getScriptEngine() != 0)
        getScriptEngine()->eventAfterShowForm(form);
}


void Essence::beforeHideFormEvent(Form* form)
{
    if (scriptEngineEnabled && getScriptEngine() != 0)
        getScriptEngine()->eventBeforeHideForm(form);
}


void Essence::afterHideFormEvent(Form* form)
{
    if (scriptEngineEnabled && getScriptEngine() != 0)
        getScriptEngine()->eventAfterHideForm(form);
}


void Essence::closeFormEvent(Form* form)
{
    if (scriptEngineEnabled && getScriptEngine() != 0)
        getScriptEngine()->eventCloseForm(form);
}


QString Essence::preparePictureUrl()
{
    QString result;
    if (scriptEngineEnabled && getScriptEngine() != 0)
        result = getScriptEngine()->preparePictureUrl(this);
    return result;
}


QString Essence::prepareBarCodeData()
{
    QString result;
    if (scriptEngineEnabled && getScriptEngine() != 0)
        result = getScriptEngine()->prepareBarCodeData(this);
    return result;
}


void Essence::afterRowChanged()
{
    if (scriptEngineEnabled && getScriptEngine() != 0 && isVisible())
        getScriptEngine()->eventAfterRowChanged();
}


void Essence::beforeRowChanged()
{
    if (scriptEngineEnabled && getScriptEngine() != 0)
        getScriptEngine()->eventBeforeRowChanged();
}


void Essence::prepareSelectCurrentRowCommand()
{
    preparedSelectCurrentRow.clear();

    // Подготовим приготовленный (PREPARE) запрос для обновления текущей строки при вычислениях
    QString command = tableModel->getSelectStatement();
    preparedSelectCurrentRow.prepare(command);
}


void Essence::updateCurrentRow()
{
    if (preparedSelectCurrentRow.exec() && preparedSelectCurrentRow.first())
    {
        QModelIndex index = getCurrentIndex();
        for (int i = 0; i < preparedSelectCurrentRow.record().count(); i++)
        {
            QString fieldName = preparedSelectCurrentRow.record().fieldName(i);
            QVariant value = preparedSelectCurrentRow.record().value(fieldName);
            if (value != tableModel->record(index.row()).value(fieldName))
                tableModel->setData(tableModel->index(index.row(), i), value, true);
        }
        setCurrentIndex(index);
    }
    else
    {
        QString command = preparedSelectCurrentRow.executedQuery();
        TApplication::exemplar()->debug(1, QString("PreparedQuery Error: %1").arg(preparedSelectCurrentRow.lastError().text()));
        TApplication::exemplar()->debug(1, QString("PreparedQuery Expression: %1").arg(command));
    }
}


void Essence::preparePrintValues()
{
    if (reportScriptEngine != 0)
    {
        // Зарядим текущую дату
        reportScriptEngine->getReportContext()->setValue("сегодня", QDate().currentDate().toString("dd.MM.yyyy"));
        // Зарядим имя пользователя
        reportScriptEngine->getReportContext()->setValue("пользователь", app->username);
        // Зарядим константы в контекст печати
        QString constDictionaryName = db->getObjectName("константы");
        QString constNameField = db->getObjectName(constDictionaryName + ".имя");
        QString constValueField = db->getObjectName(constDictionaryName + ".значение");

        // Откроем справочник констант и загрузим константы в контекст печати
        Dictionary* dict = app->getDictionaries()->getDictionary(constDictionaryName);
        dict->query();    // Прочитаем содержимое справочника констант
        MySqlRelationalTableModel* model = dict->getTableModel();
        for (int i = 0; i < model->rowCount(); i++)
        {
            QSqlRecord rec = model->record(i);
            reportScriptEngine->getReportContext()->setValue(QString("%1.%2").arg(constDictionaryName).arg(rec.value(constNameField).toString().trimmed()).toLower(), rec.value(constValueField));
        }
        // Загрузим основную таблицу в контекст печати
        QStringList fieldsList = getFieldsList();
        for (int i = 1; i <= getTableModel()->rowCount(); i++)
        {
            QSqlRecord rec = getTableModel()->record(i-1);
            foreach(QString field, fieldsList)
            {
                reportScriptEngine->getReportContext()->setValue(QString("таблица.%1").arg(field).toLower(), rec.value(field), i);
            }
            reportScriptEngine->getReportContext()->setValue(QString("таблица.%1").arg("номерстроки"), QVariant(i), i);
        }
        if (scriptEngineEnabled && scriptEngine != 0)
            scriptEngine->eventPreparePrintValues();
    }
}


void Essence::clearPrintValues()
{
    if (reportScriptEngine != 0)
    {
        reportScriptEngine->getReportContext()->getData()->clear();
    }
}


bool Essence::getFile(QString path, QString fileName, FileType type)
{
    bool result = false;
    TApplication* app = TApplication::exemplar();
    DBFactory* db = app->getDBFactory();
    QString fullFileName = path + fileName;
    if (!QDir().exists(fullFileName))
    {   // Если файл не существует, то попытаемся получить его с сервера
        QByteArray templateFile = db->getFile(fileName, type);
        if (templateFile.size() > 0)
        {   // Если удалось получить шаблон отчета, то сохраним его локально
            app->saveFile(fullFileName, &templateFile);
            result = true;
        }
    }
    else
    {   // файл существует локально
        QFile file(fullFileName);
        // Проверим, какой файл свежее, локальный или на сервере
        int diff = app->getSecDiff();
        QFileInfo fi(file);
        QDateTime locFileTime = fi.lastModified();
        locFileTime.addSecs(diff);  // Время модификации локального файла, приведенное к серверному времени
        FileInfo servFileInfo = db->getFileInfo(fileName, type);
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray array = file.readAll();
            file.close();
            qulonglong localFileCheckSum = db->calculateCRC32(&array);
            if (servFileInfo.size != localFileCheckSum)
            {   // контрольные суммы файлов не совпадают или нужно сохранить принудительно
                if (app->isSA() && (!servFileInfo.lastModified.isValid() || servFileInfo.lastModified.secsTo(locFileTime) > 5))   // Если не указано время сохранения файла на сервере
                                                                                                        // или локальный файл свежее серверного более чем на 5 секунд
                    db->setFile(fileName, type, array);      // Сохранить копию файла на сервере, если мы работаем как SA
                else
                {
                    QByteArray templateFile = db->getFile(fileName, type);
                    if (templateFile.size() > 0)
                    {   // Если удалось получить шаблон отчета, то сохраним его локально
                        app->saveFile(fullFileName, &templateFile);
                    }
                }
            }
            result = true;
        }
    }
    return result;
}


void Essence::saveOldValues()
{
    // Сохраним старые значения полей записи
    oldValues.clear();
    foreach (QString field, tableModel->getFieldsList())
    {
        QModelIndex index;
        index = tableModel->index(getCurrentRow(), tableModel->fieldIndex(field));
        QVariant val = tableModel->data(index);
        oldValues.insert(field, val);
    }
}


void Essence::restoreOldValues()
{
    bool oldDoSubmit = doSubmit;
    doSubmit = false;
    foreach (QString fieldName, oldValues.keys())
    {
        if (getValue(fieldName) != oldValues.value(fieldName))
            setValue(fieldName, oldValues.value(fieldName));
    }
    doSubmit = oldDoSubmit;
    db->clearCommands();
}


void Essence::barCodeReaded(QString barCode)
{
    if (scriptEngineEnabled && scriptEngine != 0 && enabled)
    {
        scriptEngine->eventBarCodeReaded(barCode);
    }

    if (grdTable != 0)
        grdTable->setCurrentFocus();
    form->setButtons();
}


void Essence::cardCodeReaded(QString cardCode)
{
    if (scriptEngineEnabled && scriptEngine != 0 && enabled && cardReaderEnabled)
        scriptEngine->eventCardCodeReaded(cardCode);
}


void Essence::printLabel(QString fileName, int copyCount)
{
    if (app->getConfigValue("BAR_CODE_PRINTER_NEEDED").toBool() && rowCount() > 0)
    {
        QString printerName = app->getConfigValue("BAR_CODE_PRINTER_NAME").toString();
        QString labelSize = app->getConfigValue("BAR_CODE_PRINTER_BARCODESIZE").toString();
        bool preview = app->getConfigValue("BAR_CODE_PRINTER_BARCODEPREVIEW").toBool();
        print(fileName + "(" + labelSize + ").ods", false, !preview, copyCount, printerName);
    }
}


void Essence::print(QString fileName, bool newFile, bool justPrint, int copyCount, QString printerName)
// fileName - файл с шаблоном документа
{
    bool result = true;                         // По умолчанию документ будет печататься
    // Подготовим контекст для печати
    QHash<QString, QVariant> printValues;
    // Создадим скриптовый обработчик контекста печати
    reportScriptEngine = new DocumentScriptEngine(&printValues, this);
//    reportScriptEngine = scriptEngine;
    // Заполним контекст данными
    preparePrintValues();

    if (reportScriptEngine->open(fileName + ".js"))    // Если имеются скрипты, то запустим их и получим результат
    {
        result = reportScriptEngine->evaluate();       // Если скрипты вернут отрицательный результат, то документ не напечатается
    }

    if (result)
    {
        // Найдем полный путь к файлам с шаблонами
        QString fullFileName = app->getReportsPath();

        // Если нет каталога с отчетами, то создадим его
        if (!QDir(fullFileName).exists())
            QDir().mkpath(fullFileName);

        fullFileName += fileName;

        // Если такого шаблона нет, попробуем получить его с сервера
        getFile(app->getReportsPath(), fileName, ReportTemplateFileType);

        QString ext = QFileInfo(fileName).suffix();
        if (newFile)
        {
            QFile().copy(app->applicationDirPath() + "/empty.ods", fullFileName);
        }
        else
        {
            QString tmpFileName = QDir::tempPath() + "/qt_temp_XXXXXX." + ext;
            // Скопируем шаблон во временный файл
            QTemporaryFile templateFile(tmpFileName);
            if (templateFile.open())
            {
                tmpFileName = templateFile.fileName();
                templateFile.close();
                templateFile.remove();

                // Скопируем файл отчета (шаблон) во временный файл
                QFile().copy(fullFileName, tmpFileName);
            }
            fullFileName = tmpFileName;
        }
        if (QDir().exists(fullFileName))
        {
            // На 3 секунды выведем сообщение об открытии документа
            app->showMessageOnStatusBar(trUtf8("Открывается документ: ") + fileName, 3000);

            // Из пользовательских настроек выберем обработчик шаблона
            switch (app->getReportTemplateType())
            {
                // Обработчик шаблона запускает OpenOffice, для которого нужны специально подготовленные шаблоны с внутренними функциями
                case OOreportTemplate:
                {
                    OOReportEngine* report = new OOReportEngine(reportScriptEngine);
                    if (report->open())
                    {
                        report->open(&printValues, fileName, ext);
                        report->close();
                    }
                    delete report;
                }
                break;
/*
                    // Обработчик шаблона с использованием OpenOffice UNO. С UNO работает медленно, поэтому не вижу смысла разрабатывать
                    case OOUNOreportTemplate:
                        {   // в пользовательских настройках стоит использовать ОО в качестве движка печати
                            OOUNOReportEngine* report = new OOUNOReportEngine(&scriptEngine);
                            if (report->open())
                            {
                               report->open(tmpFileName, &printValues);
                                report->close();
                            }
                            delete report;
                        }
                        break;
*/
                // Обработчик шаблона с "потрошением" родных файлов OpenOffice. Это основной обработчик в настоящее время
                case OOXMLreportTemplate:
                {   // в пользовательских настройках стоит использовать ОО в качестве движка печати
                    OOXMLReportEngine* report = new OOXMLReportEngine(this, reportScriptEngine);
                    if (report->open())
                    {
                        report->setFileName(fileName);
                        report->open(fullFileName, reportScriptEngine->getReportContext(), justPrint, copyCount, printerName);
                        report->close();
                    }
                    delete report;
                }
                break;
                // Обработчик шаблона с подключение проекта OpenRPT, который предлагал Drake. С его уходом ветка умерла.
                case OpenRPTreportTemplate:
                {   // в пользовательских настройках стоит использовать ОО в качестве движка печати
//                              OpenRPTreportEngine report(&printValues, file, ext);
//                           report.open();
                }
                break;
            }
        }
    }
    delete reportScriptEngine;
    reportScriptEngine = 0;
}


bool Essence::isDocumentLoading()
{
    if (dictionaries != 0 && dictionaries->getDocument() != 0)
    {
        // И в данный момент происходит загрузка документа из файла (или другого источника)
        if (dictionaries->getDocument()->isLoading())
            return true;
    }
    return false;
}


QModelIndex Essence::getCurrentIndex()
{
    QModelIndex index;
    if (grdTable != 0)
    {
        index = grdTable->currentIndex();
    }
    return index;
}


void Essence::setCurrentIndex(QModelIndex index)
{
    if (grdTable != 0)
        grdTable->setCurrentIndex(index);
}


QVariant Essence::getSumValue(QString name)
{   // Возвращает сумму полей <name> всех строк документа
    double sum = 0;
    int col = tableModel->record().indexOf(name);
    for (int j = 0; j < tableModel->rowCount(); j++)
    {
        double value = tableModel->data(tableModel->index(j, col)).toDouble();
        sum += value;
    }
    return QVariant(sum);
}


void Essence::setCardReaderEnabled(bool enabled)
{
    cardReaderEnabled = enabled;
}
