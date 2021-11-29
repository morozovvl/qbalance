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
#include <QtCore/QFile>
#include <QtCore/QTemporaryFile>
#include <QtCore/QDebug>
#include <QtGui/QImage>
//#include <boost/crc.hpp>
#include "essence.h"
#include "../kernel/app.h"
#include "../kernel/document.h"
#include "../kernel/dictionaries.h"
#include "../gui/myprogressdialog.h"
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
    grdTable = 0 /*nullptr*/;
    tableModel = 0 /*nullptr*/;
    form = 0 /*nullptr*/;
    parentForm = 0 /*nullptr*/;
    scriptEngine = 0 /*nullptr*/;
    reportScriptEngine = 0 /*nullptr*/;
    m_networkAccessManager = 0 /*nullptr*/;
    menuMode = false;
    isView = false;
}


Essence::~Essence() {
    this->disconnect();
}


void Essence::postInitialize(QString name, QObject* parent)
{
    Table::postInitialize(name, parent);

    form = 0 /*nullptr*/;
    scriptEngine = 0 /*nullptr*/;
    parentForm = app->getMainWindow()->centralWidget();
    formTitle   = "";
    lInsertable = false;
    lDeleteable = false;
    lViewable   = false;
    lUpdateable = false;
    lPrintable  = false;
    isDictionary = true;
    enabled     = true;
    sortedTable = true;
    idFieldName = db->getObjectName("код");
    nameFieldName = db->getObjectName("имя");
    isView = db->isView(tableName);
    scriptFileName =  tagName;
    if (tagName.size() > 0)
        scriptFileName += ".qs";
    scriptEngineEnabled = true;                 // По умолчанию разрешена загрузка скриптового движка
    photoPath = "";
    photoPathVerified = false;
    photoIdField = "";
    photoEnabled = false;
    m_networkAccessManager = 0 /*nullptr*/;
    doSubmit = false;                           // По умолчанию не обновлять записи автоматически
    defaultFilter = "";
    grdTable = 0 /*nullptr*/;
    dictionaries = 0 /*nullptr*/;
    loading = false;
    reportScriptEngine = 0 /*nullptr*/;
    lIsDocument = false;
    cardReaderEnabled = false;
    modified = false;
}


bool Essence::open(QString command)
{
    if (Table::open(command))
    {
        if (!app->isScriptMode())       // Если мы работаем не в скриптовом режиме, то создадим форму для этой сущности
            initForm();

        if (form != 0 /*nullptr*/)
        {
            grdTable = form->getGrdTable();
            if (grdTable != 0 /*nullptr*/)
            {
                grdTable->setEssence(this);
                grdTable->setReadOnly(!lUpdateable);
            }
        }

        openScriptEngine();
        openReportScriptEngine();

        return true;
    }
    return false;
}


void Essence::close()
{
    closeReportScriptEngine();
    closeScriptEngine();

    if (form != 0 /*nullptr*/)
    {
        form->close();
        if (form->isDefaultForm())
        {
            delete form;
            form = 0 /*nullptr*/;
        }
        else
            form->deleteLater();
    }

    if (m_networkAccessManager != 0 /*nullptr*/)
        delete m_networkAccessManager;

    Table::close();
}


bool Essence::isFieldExists(QString field)
{
    return getFieldsList().contains(field);
}


void Essence::setDoSubmit(bool submit)
{
    doSubmit = submit;
}


void Essence::setFilterEnabled(bool enabled)
{
    filterEnabled = enabled;
}


void Essence::setFilter(const QString &filter)
{
    defaultFilter = filter;
}


int Essence::getRowCount()
{
    return tableModel != 0 /*nullptr*/ ? tableModel->rowCount() : 0;
}


int Essence::rowCount()
{
    return getRowCount();
}


FormGrid* Essence::getForm()
{
    return form;
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
}


bool Essence::isDeleteable()
{
    return lDeleteable;
}


bool Essence::isViewable()
{
    return lViewable;
}


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
    return form != 0 /*nullptr*/ ? form->isDefaultForm() : false;
}


bool Essence::isFormVisible()
{
    return form != 0 /*nullptr*/ ? form->isVisible() : false;
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


void Essence::setCurrentFieldName(QString fieldName)
{
    setCurrentColumn(tableModel->fieldIndex(fieldName));
}


int Essence::getCurrentRow()
{
    return getCurrentIndex().row();
}


int Essence::getCurrentColumn()
{
    return getCurrentIndex().column();
}


void Essence::setCurrentColumn(int column)
{
    if (grdTable != 0 /*nullptr*/)
    {
        grdTable->selectColumn(column);
    }
}


void Essence::setCurrentRow(int row)
{
    if (grdTable != 0 /*nullptr*/)
    {
        grdTable->selectRow(row);
    }
    saveOldValues();
}


Dictionaries* Essence::getDictionaries()
{
    return dictionaries;
}


void Essence::setDictionaries(Dictionaries* dicts)
{
    dictionaries = dicts;
}


bool Essence::isLoading()
{
    return loading;
}


void Essence::appendPrintValue(QString name, QVariant value)
{
    if (reportScriptEngine != 0 /*nullptr*/)
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
    if (reportScriptEngine != 0 /*nullptr*/)
        reportScriptEngine->getReportContext()->appendPrintValues(str, query);
}


QVariant Essence::getPrintValue(QString name)
{
    QVariant result;
    if (reportScriptEngine != 0 /*nullptr*/)
        result = reportScriptEngine->getReportContext()->getValue(name);
    return result;
}


bool Essence::isDocument()
{
    return lIsDocument;
}


void Essence::showPhoto()
{
    grdTable->showPhoto();
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
    return (form != 0 /*nullptr*/ ? form->getFormWidget() : 0 /*nullptr*/);
}


bool Essence::isVisible()
{
    return form->isVisible();
}


bool Essence::calculate(bool update)
{
    bool lResult = false;

    if (scriptEngineEnabled && scriptEngine != 0 /*nullptr*/)
    {
        scriptEngine->eventCalcTable();
        if (scriptEngine->getScriptResult())
        {
            scriptEngine->eventAfterCalculate();
            if (scriptEngine->getScriptResult())
            {
                if (scriptEngine->getScriptResult())
                {
                    lResult = true;
                }
            }
        }
    }

    if (update && !isView)
        saveChanges();

    return lResult;
}


QScriptValue Essence::evaluateScript(QString script)
{
    QScriptValue result;
    if (scriptEngine != 0 /*nullptr*/)
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
            scriptEngine->showScriptError();
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
            else if (type == QVariant::Date && result.type() == QVariant::String)
            {
                // Пока не понятно почему, но иногда результат получается строкового типа, хотя должен быть типа даты.
                result = QVariant(QDate().fromString(result.toString(), app->dateFormat()));
            }
        }
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
                if (columnsProperties.at(i).type.toUpper() == "NUMERIC")
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
        setCurrentIndex(oldIndex);
    }
}


int Essence::getId(int row)
{
    if (row < 0)
        row = getCurrentRow();
    return getValue(idFieldName, row).toInt();
}


int Essence::locateId(int id)
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


bool Essence::setId(int id)
{
    bool result = false;
    bool enabled = photoEnabled;
    photoEnabled = false;
    if (getValue(idFieldName) != id)
    {
        // На время отключим обновление(показ) фотографии
        query(QString("\"%1\".\"%2\"=%3").arg(tableName).arg(idFieldName).arg(id), true);
    }
    if (grdTable != 0 /*nullptr*/)
    {
        grdTable->selectRow(0);
        grdTable->setCurrentIndex(grdTable->currentIndex().sibling(0, grdTable->currentIndex().column()));
    }
    photoEnabled = enabled;

    result = (getValue(idFieldName).toInt() == id);

    return result;
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
    if (row >= 0)
        setCurrentRow(row);

    if (form != 0 /*nullptr*/)
        form->setButtons();
 }


QString Essence::getPhotoPath()
{
    QString path;
    // Попробуем получить локальный путь к фотографии
    if (isDictionary && photoPath.size() == 0 && !photoPathVerified)
    {
        // Если путь, откуда нужно брать фотографии не установлен, то установим его по умолчанию для данного справочника
        path = db->getDictionaryPhotoPath(tableName);
        photoPath = path;
        photoPathVerified = true;           // Чтоб больше не спрашивала
    }
    else
        path = photoPath;
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
        if (photoIdField.size() == 0 && isDictionary)
        {
            // Если имя поля, из которого нужно брать идентификатор фотографии не установлено, то будем считать идентификатором код позиции
            photoIdField = db->getObjectName("код");
        }

        // Теперь получим значение идентификатора
        if (tableModel->rowCount() > 0 && photoIdField.size() > 0)
        {
            if (photoPath.size() > 0 && photoEnabled)
            {
                localFile = getLocalPhotoFile(getPhotoPath());       // Запомним локальный путь к фотографии на случай обращения к серверу за фотографией
                idValue = getValue(photoIdField).toString().trimmed();
                file = getLocalPhotoFile();
                if (isDictionary && file.size() > 0)
                {
                    if ((!QFile(file).exists() || !app->isSA()) && phEnabled)
                    {   // Локальный файл с фотографией не найден, попробуем получить фотографию с нашего сервера. Будем делать это только для справочника, а не для документа
                        // Мы знаем, под каким именем искать фотографию на нашем сервере, то попробуем обратиться к нему за фотографией
                        QByteArray picture = db->getFile(localFile, PictureFileType, true); // Получить файл с картинкой из расширенной базы
                        if (picture.size() > 0)
                        {   // Если удалось получить какую-то фотографию
                            app->saveFile(file, &picture);
                            if (copyTo.size() > 0 && app->isSA())
                                app->saveFileToServer(app->getPhotosPath(copyTo), file, PictureFileType, true);   // Если указано, что фотографию нужно скопировать, то скопируем ее
                        }
                        if (!QFile(file).exists() && app->isSA())
                        {   // Фотография не найдена на сервере, попробуем получить фотографию из Интернета
                            pictureUrl = preparePictureUrl();
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
                                        if (m_networkAccessManager == 0 /*nullptr*/)
                                        {   // Вызывается только один раз, по необходимости загрузить фотографию
                                            m_networkAccessManager = new QNetworkAccessManager(this);
                                            connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
                                        }
                                        if (m_networkAccessManager != 0 /*nullptr*/)
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
                        if (app->isSA())
                        {
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
                    if (scriptEngineEnabled && scriptEngine != 0 /*nullptr*/)
                        scriptEngine->eventPhotoLoaded();
                }
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
        if (app->showYesNo(QObject::trUtf8("Удалить запись? Вы уверены?")) == QMessageBox::Yes)
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
    modified = false;
    if (dictionaries != 0 /*nullptr*/)
    {
        Document* doc = dictionaries->getDocument();
        if (doc != 0 /*nullptr*/)
            doc->setModified(modified);
    }

    if (!opened)
        open();
    if (opened && form != 0 /*nullptr*/)
    {
        beforeShowFormEvent(getForm());
        form->exec();
        afterShowFormEvent(getForm());
    }
    return result;
}


void Essence::show()
{
    modified = false;
    if (dictionaries != 0 /*nullptr*/)
    {
        Document* doc = dictionaries->getDocument();
        if (doc != 0 /*nullptr*/)
            doc->setModified(modified);
    }


    if (!opened)
        open();
    if (opened && form != 0 /*nullptr*/)
    {
        beforeShowFormEvent(getForm());
        form->show();
        afterShowFormEvent(getForm());
    }
}


void Essence::hide()
{
    if (opened && form != 0 /*nullptr*/)
    {
        if (beforeHideFormEvent(form))
        {
            form->hide();
            afterHideFormEvent(form);
        }
    }
}


void Essence::view()
{
    if (form != 0 /*nullptr*/)
        form->getFormWidget()->setFocus(Qt::OtherFocusReason);
}


void Essence::openScripts()
{
    openScriptEngine();
    openReportScriptEngine();
}


void Essence::setScriptEngine()
{
    scriptEngine = new ScriptEngine(this);
}


void Essence::evaluateEngine()
{
    if (scriptEngineEnabled && scriptEngine != 0 /*nullptr*/)
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


DocumentScriptEngine* Essence::getReportScriptEngine()
{
    return reportScriptEngine;
}


ReportContext* Essence::getReportContext()
{
    return reportScriptEngine->getReportContext();
}


void Essence::openScriptEngine()
{
    if (scriptEngineEnabled && scriptEngine == 0 /*nullptr*/)
    {
        if (scriptFileName.size() > 0)
        {
            setScriptEngine();
            evaluateEngine();
            if (dictionaries != 0 /*nullptr*/ && dictionaries->getDocument() != 0 /*nullptr*/)          // Если этот справочник является частью документа
                scriptEngine->setIsDocumentScript(true);                                             // То обозначим контекст выполнения скриптов

            initFormEvent();
        }
    }
}


void Essence::closeScriptEngine()
{
    closeFormEvent(form);

    if (scriptEngine != 0 /*nullptr*/)
    {
        scriptEngine->close();
        scriptEngine->deleteLater();
        scriptEngine = 0 /*nullptr*/;
    }
}


void Essence::openReportScriptEngine()
{
    if (scriptEngineEnabled && reportScriptEngine == 0 /*nullptr*/)
    {
        reportScriptEngine = new DocumentScriptEngine(&printValues, this);
        reportScriptEngine->open();
    }
}


void Essence::closeReportScriptEngine()
{
    if (reportScriptEngine != 0 /*nullptr*/)
    {
        reportScriptEngine->close();
        delete reportScriptEngine;
        reportScriptEngine = 0 /*nullptr*/;
    }
}


void Essence::setEnabled(bool en)
{
    QString disabledMessage = QObject::trUtf8(" - изменения запрещены");
    enabled = en;
    if (scriptEngineEnabled && scriptEngine != 0 /*nullptr*/)
        scriptEngine->eventSetEnabled(en);
    if (enabled)
        setFormTitle(getFormTitle().remove(disabledMessage));
    else
    {
        if (!getFormTitle().contains(disabledMessage))
            setFormTitle(form->getFormWidget()->windowTitle().append(disabledMessage));
    }
    if (form != 0 /*nullptr*/)
        form->setEnabled(enabled);
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
    if (form != 0 /*nullptr*/)
        form->getFormWidget()->setWindowTitle(title);
}


QString Essence::getFormTitle()
{
    if (form != 0 /*nullptr*/)
        return form->getFormWidget()->windowTitle();
    return QString();
}


bool Essence::isFormSelected()
{
    if (form != 0 /*nullptr*/)
        return form->isFormSelected();
    return false;
}


void Essence::cmdOk()
{
    saveChanges();
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
    if (scriptEngineEnabled && getScriptEngine() != 0 /*nullptr*/)
        getScriptEngine()->eventInitForm(form);
}


void Essence::beforeShowFormEvent(Form* form)
{
    if (scriptEngineEnabled && getScriptEngine() != 0 /*nullptr*/)
        getScriptEngine()->eventBeforeShowForm(form);
}


void Essence::afterShowFormEvent(Form* form)
{
    if (scriptEngineEnabled && getScriptEngine() != 0 /*nullptr*/)
        getScriptEngine()->eventAfterShowForm(form);
}


bool Essence::beforeHideFormEvent(Form* form)
{
    bool result = true;
    if (scriptEngineEnabled && getScriptEngine() != 0 /*nullptr*/)
        result = getScriptEngine()->eventBeforeHideForm(form);
    return result;
}


void Essence::afterHideFormEvent(Form* form)
{
    if (scriptEngineEnabled && getScriptEngine() != 0 /*nullptr*/)
        getScriptEngine()->eventAfterHideForm(form);
}


void Essence::closeFormEvent(Form* form)
{
    if (scriptEngineEnabled && getScriptEngine() != 0 /*nullptr*/)
        getScriptEngine()->eventCloseForm(form);
}


QString Essence::preparePictureUrl()
{
    QString result;
    if (scriptEngineEnabled && getScriptEngine() != 0 /*nullptr*/)
        result = getScriptEngine()->preparePictureUrl(this);
    return result;
}


QString Essence::prepareBarCodeData()
{
    QString result;
    if (scriptEngineEnabled && getScriptEngine() != 0 /*nullptr*/)
        result = getScriptEngine()->prepareBarCodeData(this);
    return result;
}


void Essence::afterRowChanged()
{
    if (scriptEngineEnabled && getScriptEngine() != 0 /*nullptr*/ && isVisible())
        getScriptEngine()->eventAfterRowChanged();
}


void Essence::beforeRowChanged()
{
    if (scriptEngineEnabled && getScriptEngine() != 0 /*nullptr*/)
        getScriptEngine()->eventBeforeRowChanged();
}


void Essence::prepareSelectCurrentRowCommand()
{
    preparedSelectCurrentRow.clear();

    // Подготовим приготовленный (PREPARE) запрос для обновления текущей строки при вычислениях
    QString command = tableModel->getSelectStatement();
    preparedSelectCurrentRow.prepare(command);
}


void Essence::updateCurrentRow(int strNum)
{
    bool execRes = preparedSelectCurrentRow.exec();
    bool firstRes = preparedSelectCurrentRow.first();
    if (execRes && firstRes)
    {
        QModelIndex index = getCurrentIndex();
        int str = strNum == 0 ? index.row() : strNum;
        for (int i = 0; i < preparedSelectCurrentRow.record().count(); i++)
        {
            QString fieldName = preparedSelectCurrentRow.record().fieldName(i);
            QVariant value = preparedSelectCurrentRow.record().value(fieldName);
            QVariant recValue = tableModel->record(str).value(fieldName);
            if (value != recValue)
            {
                tableModel->setData(tableModel->index(str, i), value, true);
            }
        }
        setCurrentIndex(index);
    }
    else
    {
        QString command = preparedSelectCurrentRow.executedQuery();
        if (preparedSelectCurrentRow.lastError().isValid())
        {
            TApplication::exemplar()->debug(1, QString("PreparedQuery Error: %1").arg(preparedSelectCurrentRow.lastError().text()));
            TApplication::exemplar()->debug(1, QString("PreparedQuery Expression: %1").arg(command));
        }
    }
    saveOldValues();
}


void Essence::preparePrintValues()
{
    if (reportScriptEngine != 0 /*nullptr*/)
    {
        // Зарядим текущую дату
        reportScriptEngine->getReportContext()->setValue("сегодня", QDate().currentDate().toString(app->dateFormat()));
        // Зарядим имя пользователя
        reportScriptEngine->getReportContext()->setValue("пользователь", app->login);
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
        for (int i = 1; i <= rowCount(); i++)
        {
            QSqlRecord rec = getTableModel()->record(i-1);
            foreach(QString field, fieldsList)
            {
                reportScriptEngine->getReportContext()->setValue(QString("таблица.%1").arg(field).toLower(), rec.value(field), i);
            }
            reportScriptEngine->getReportContext()->setValue(QString("таблица.%1").arg("НОМЕРСТРОКИ"), QVariant(i), i);
        }

        reportScriptEngine->getReportContext()->setValue(QString("таблица.%1").arg("КОЛСТРОК"), rowCount());

        if (scriptEngineEnabled && scriptEngine != 0 /*nullptr*/)
            scriptEngine->eventPreparePrintValues();
    }
}


void Essence::clearPrintValues()
{
    if (reportScriptEngine != 0 /*nullptr*/)
    {
        reportScriptEngine->getReportContext()->clear();
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
//        if (app->getConfigValue("PERMANENT_FRESH_TEST").toBool())
//        {
            QFile file(fullFileName);
            // Проверим, какой файл свежее, локальный или на сервере
            int diff = db->getSecDiff();
            QFileInfo fi(file);
            QDateTime locFileTime = fi.lastModified();
            locFileTime = locFileTime.addSecs(diff);  // Время модификации локального файла, приведенное к серверному времени
            FileInfo servFileInfo = db->getFileInfo(fileName, type);
            if (file.open(QIODevice::ReadOnly))
            {
                QByteArray array = file.readAll();
                file.close();

                qulonglong localFileCheckSum = app->calculateCRC32(&array);

                if (servFileInfo.size != localFileCheckSum) // Если локальный и серверный файлы различаются по контрольной сумме
                {
                    if (app->isSA())   // Если не указано время сохранения файла на сервере
                    {
                        QByteArray templateFile = db->getFile(fileName, type);
                        app->saveFile(fullFileName, &templateFile);
                    }
                    else
                    {
                        QByteArray templateFile = db->getFile(fileName, type);
                        app->saveFile(fullFileName, &templateFile);
                    }
                }
            }
//        }
        result = true;
    }
    return result;
}


void Essence::saveOldValues()
{
    // Сохраним старые значения полей записи
    oldValues.clear();
    if (tableModel != 0 /*nullptr*/ && tableModel->rowCount()> 0)
    {
        foreach (QString field, tableModel->getFieldsList())
        {
            QModelIndex index;
            index = tableModel->index(getCurrentRow(), tableModel->fieldIndex(field));
            QVariant val = tableModel->data(index);
            oldValues.insert(field, val);
        }
    }
}


void Essence::restoreOldValues()
{
    foreach (QString fieldName, oldValues.keys())
    {
        if (getValue(fieldName) != oldValues.value(fieldName))
            setValue(fieldName, oldValues.value(fieldName));
    }
    db->clearCommands();    // Забудем команды, которые приготовили для сохранения изменений
    grdTable->repaint();
}


bool Essence::barCodeReaded(QString barCode)
{
    bool result = false;
    if (scriptEngineEnabled && scriptEngine != 0 /*nullptr*/ && enabled)
    {
        result = scriptEngine->eventBarCodeReaded(barCode);
    }

    if (grdTable != 0 /*nullptr*/)
        grdTable->setCurrentFocus();
    form->setButtons();
    return result;
}


void Essence::cardCodeReaded(QString cardCode)
{
    if (scriptEngineEnabled && scriptEngine != 0 /*nullptr*/ && enabled && cardReaderEnabled && form != 0 /*nullptr*/)
    {
        Dialog* frm = form->getFormWidget();
        if (frm != 0 /*nullptr*/ && frm->isVisible() && frm == app->getActiveSubWindow()->widget())
        {
            scriptEngine->eventCardCodeReaded(cardCode);
        }
    }
}


void Essence::printLabel(QString fileName, int copyCount)
{
    if (app->getConfigValue("BAR_CODE_PRINTER_NEEDED").toBool() && rowCount() > 0)
    {
        QString printerName = app->getConfigValue("BAR_CODE_PRINTER_NAME").toString();
        QString labelSize = app->getConfigValue("BAR_CODE_PRINTER_BARCODESIZE").toString();
        bool preview = app->getConfigValue("BAR_CODE_PRINTER_BARCODEPREVIEW").toBool();
        print(fileName + "(" + labelSize + ").ods", false, !preview, copyCount, printerName, getCurrentRow() + 1);
    }
}


void Essence::printLabel1(QString fileName, int strNumber)
{
    QString printerName = app->getConfigValue("BAR_CODE_PRINTER_NAME").toString();
    bool preview = app->getConfigValue("BAR_CODE_PRINTER_BARCODEPREVIEW").toBool();
    print(fileName, false, !preview, 1, printerName, strNumber);
}


void Essence::print(QString fileName, bool newFile, bool justPrint, int copyCount, QString printerName, int strNumber)
// fileName - файл с шаблоном документа
{
    bool result = true;                         // По умолчанию документ будет печататься

    preparePrintValues();

    if (reportScriptEngine != 0 /*nullptr*/)
    {
        if (reportScriptEngine->open(fileName + ".js"))    // Если имеются скрипты, то запустим их и получим результат
            result = reportScriptEngine->evaluate();       // Если скрипты вернут отрицательный результат, то документ не напечатается
    }
    else
        result = false;

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
                    if (report->open(fullFileName, reportScriptEngine->getReportContext()))
                    {
                        if (report->makeReport(copyCount, strNumber))
                            report->preview(justPrint, printerName);
                    }
                    report->close();
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
    clearPrintValues();
}


bool Essence::isDocumentLoading()
{
    if (dictionaries != 0 /*nullptr*/ && dictionaries->getDocument() != 0 /*nullptr*/)
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
    if (grdTable != 0 /*nullptr*/)
    {
        index = grdTable->currentIndex();
    }
    return index;
}


void Essence::setCurrentIndex(QModelIndex index)
{
    if (grdTable != 0 /*nullptr*/)
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


void Essence::submit()
{
    if (!isView)
    {
        // Сохраним в БД все столбцы. Будут сохраняться только те, в которых произошли изменения
        int row = getCurrentRow();

        for (int i = 0; i < tableModel->record().count(); i++)
        {
            QString fieldName = tableModel->record().fieldName(i);
            QVariant oldValue = getOldValue(fieldName);
            QVariant newValue = getValue(fieldName);

            if (oldValue.isValid() && newValue != oldValue)    // Для экономии трафика и времени посылать обновленные данные на сервер будем в случае, если данные различаются
                tableModel->prepareCommand(tableModel->index(row, i));
        }
    }
}


bool Essence::saveChanges()
{
    bool lResult = false;

    if (!(app->isAppendFromQuery() && QString(metaObject()->className()).compare("Documents", Qt::CaseInsensitive) == 0))
    {
        submit();

        if (db->execCommands())
        {
            updateCurrentRow();

            modified = true;
            if (dictionaries != 0 /*nullptr*/)
            {
                Document* doc = dictionaries->getDocument();
                if (doc != 0 /*nullptr*/)
                    doc->setModified(modified);
            }

            lResult = true;
        }
        else       // Во время сохранения результатов произошла ошибка
            restoreOldValues();
    }
    else
    {
        lResult = true;
    }
    return lResult;
}


void Essence::exportData(QString, QStringList fieldsList)
{
    QStringList fList = fieldsList.count() > 0 ? fieldsList : fieldList;
    QString fieldListCommand;
    MyProgressDialog* progressDialog;

    progressDialog = app->getMyProgressDialog(trUtf8("Ожидайте окончания экспорта данных..."));
    progressDialog->resize(600, progressDialog->height());
    progressDialog->show();

    for (int i = 0; i < fList.count(); i++)
    {
        if (fieldListCommand.size() > 0)
            fieldListCommand.append(",");
        fieldListCommand.append(fList.at(i));
    }

    QSqlQuery query = db->execQuery(QString("SELECT %1 FROM %2 ORDER BY %3").arg(fieldListCommand).arg(tableName).arg(idFieldName));
    progressDialog->setMaximum(query.size());

    if (query.first())
    {
        int i = 0;
        do
        {
            QString commandValues;
            for (int j = 0; i < query.record().count(); j++)
            {
                if (commandValues.size() > 0)
                    commandValues.append(",");
                commandValues.append(tableModel->prepareValueToWrite(columnsProperties.at(j).name, query.record().value(j), columnsProperties.at(j).precision));
            }

            QString command(QString("INSERT INTO %1 (%2) VALUES (%3);").arg(tableName).arg(fieldListCommand));
            progressDialog->setValue(i);

            i++;
        } while (query.next());
    }

    progressDialog->hide();
    delete progressDialog;
}


void Essence::setReadOnly(bool ro)
{
    tableModel->setReadOnly(ro);
    form->setEnabled(!ro);
}


TableView* Essence::getGrdTable()
{
    return grdTable;
}


void Essence::setGrdTable(TableView* gt)
{
    if (gt != 0 /*nullptr*/)
    {
        grdTable = gt;
        grdTable->setEssence(this);
    }
}


void Essence::setMenuMode(bool mm)
{
    menuMode = mm;
}


bool Essence::isMenuMode()
{
    return menuMode;
}


bool Essence::isModified()
{
    return modified;
}


void Essence::setModified(bool m)
{
    modified = m;
}
