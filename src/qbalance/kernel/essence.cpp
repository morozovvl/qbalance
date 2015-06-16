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
#include <QtCore/QHash>
#include <QtCore/QDir>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QMessageBox>
#include <QMenu>
#include <QtCore/QFile>
#include <QtCore/QTemporaryFile>
#include <QDebug>
//#include <boost/crc.hpp>
#include "essence.h"
#include "../kernel/app.h"
#include "../kernel/document.h"
#include "../gui/form.h"
#include "../gui/formgridsearch.h"
#include "../gui/mainwindow.h"
#include "../report/reportengine.h"
#include "../report/ooreportengine.h"
//#include "../report/oounoreportengine.h"
#include "../report/ooxmlreportengine.h"
#include "../engine/reportcontext.h"


Essence::Essence(QString name, QObject *parent): Table(name, parent)
{
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
    idFieldName = db->getObjectName("код");
    nameFieldName = db->getObjectName("имя");
    scriptFileName =  tagName + ".qs";
    scriptEngineEnabled = true;                 // По умолчанию разрешена загрузка скриптового движка
    photoPath = "";
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
}


Essence::~Essence() {
    this->disconnect();
}


Dialog* Essence::getFormWidget() {
    if (!opened)
    {
        open();
    }
    return (form != 0 ? form->getFormWidget() : 0);
}


bool Essence::calculate()
{
    if (scriptEngine != 0)
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
    if (n.size() > 0)
    {
        QString name = n.toUpper();
        QSqlRecord record = tableModel->record();
        if (record.contains(name))
        {
            if (row >= 0)
            {
                result =  tableModel->record(row).value(name);
            }
            else
            {
                int r = 0;
                if (grdTable != 0 && grdTable->currentIndex().isValid())
                    r = grdTable->currentIndex().row();

                result = tableModel->record(r).value(name);
            }
            QVariant::Type type = record.field(name).type();
            if (type == QVariant::Double ||
                type == QVariant::Int)
            {
                if (!result.isValid())
                    result = QVariant(0);
                result.convert(type);
                result = QString::number(result.toDouble(), 'f', record.field(name).precision()).toDouble();
            }

            // Округлим значение числового поля до точности как и в БД
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
        QModelIndex index, oldIndex;

        if (row >= 0 && form != 0)
            oldIndex = grdTable->currentIndex();

        index = tableModel->index((row >= 0 ? row : grdTable->currentIndex().row()), fieldColumn);

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
                    tableModel->setData(index, value);
                break;
            }
        }

        tableModel->submit(index);

        if (doSubmit)
            db->execCommands();

        if (row >= 0 && form != 0 && oldIndex.isValid())
            grdTable->setCurrentIndex(oldIndex);
    }
    else
        app->showError(QObject::trUtf8("Не существует колонки ") + n);
}


qulonglong Essence::getId(int row)
{
    if (row >= 0)
        return getValue(idFieldName, row).toULongLong();
    int r = grdTable->currentIndex().isValid() ? grdTable->currentIndex().row() : 0;
    return getValue(idFieldName, r).toULongLong();
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


QString Essence::getName(int row)
{
    if (row >= 0)
        return getValue(nameFieldName, row).toString().trimmed();
    int r = grdTable->currentIndex().isValid() ? grdTable->currentIndex().row() : 0;
    return getValue(nameFieldName, r).toString().trimmed();
}


void Essence::setId(qulonglong id)
{
    if (getValue(idFieldName) != id)
    {
        // На время отключим обновление(показ) фотографии
        bool enabled = photoEnabled;
        photoEnabled = false;
        query(QString("\"%1\".\"%2\"=%3").arg(tableName).arg(idFieldName).arg(id));
        photoEnabled = enabled;
    }
    grdTable->selectRow(0);
}


void Essence::query(QString filter)
{
    QModelIndex index;
    if (grdTable != 0)
    {
        index = grdTable->currentIndex();
    }
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
    if (grdTable != 0 && index.isValid())
    {
        grdTable->setCurrentIndex(index);
    }
 }


QString Essence::getPhotoPath()
{
    QString path;
    // Попробуем получить локальный путь к фотографии
    if (isDictionary && photoPath.size() == 0)
    {
        // Если путь, откуда нужно брать фотографии не установлен, то установим его по умолчанию для данного справочника
        path = db->getDictionaryPhotoPath(tableName);
        if (path.size() == 0)
            photoEnabled = false;
        photoPath = path;
    }
    else
    {
        path = photoPath;
    }
    return path;
}



QString Essence::getLocalPhotoFile()
{
    QString result;
    QString idValue = getValue(photoIdField).toString().trimmed();
    if (idValue.size() > 0)
    {
        result = app->getPhotosPath(getPhotoPath()) + "/" + idValue + ".jpg";
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

    // Если справочник является частью документа
    if (isDocumentLoading())
    {
        phEnabled = false;          // То загрузка фотографий запрещена
        copyTo = "";                // И копирование тоже
    }

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
            pictureUrl = preparePictureUrl();
            idValue = getValue(photoIdField).toString().trimmed();
            if (idValue.size() > 0)
            {
                localFile = getPhotoPath() + "/" + idValue + ".jpg";       // Запомним локальный путь к фотографии на случай обращения к серверу за фотографией
                file = getLocalPhotoFile();
                if (!QFile(file).exists())
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
                                app->saveFileToServer(app->getPhotosPath() + "/" + copyTo, file, PictureFileType, true);   // Если указано, что фотографию нужно скопировать, то скопируем ее
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
                    if (app->isSA())
                        app->saveFileToServer(file, localFile, PictureFileType, true);
                    if (copyTo.size() > 0)
                        db->copyFile(localFile, PictureFileType, copyTo, true);
                }
            }
        }
    }
    return file;
}


void Essence::removePhoto()
{
    QString idValue = getValue(photoIdField).toString().trimmed();
    if (idValue.size() > 0)
    {
        QString photoFile = app->getPhotosPath(getPhotoPath()) + "/" + idValue + ".jpg";
        QString localFile = getPhotoPath() + "/" + idValue + ".jpg";       // Запомним локальный путь к фотографии на случай обращения к серверу за фотографией

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
        if (idValue.size() > 0)
        {
            QString file = app->getPhotosPath(getPhotoPath()) + "/" + idValue + ".jpg";
            QByteArray array = reply->readAll();
            if (array.size() > 0)
            {
                app->saveFile(file, &array);
                app->showMessageOnStatusBar(QString(tr("Загружена фотография с кодом %1. Осталось загрузить %2")).arg(idValue).arg(urls.size()), 3000);

                if (copyTo.size() > 0)
                    app->saveFileToServer(app->getPhotosPath() + "/" + copyTo, file, PictureFileType, true);   // Если указано, что фотографию нужно скопировать, то скопируем ее

                // Проверим, не нужно ли обновить фотографию
                if (idValue == getValue(photoIdField).toString().trimmed())
                {
                    emit photoLoaded();                 // Выведем фотографию на экран
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
    bool result;
    if (!opened)
        open();
    if (opened && form != 0)
    {
        activeWidget = app->activeWindow();     // Запомним, какой виджет был активен, потом при закрытии этого окна, вернем его

//        beforeShowFormEvent(form);
        result = form->exec();
//        afterShowFormEvent(form);

        return result;
    }
    return 0;
}


void Essence::show()
{
    if (!opened)
        open();
    if (opened && form != 0)
    {
        activeWidget = app->activeWindow();     // Запомним, какой виджет был активен, потом при закрытии этого окна, вернем его

//        beforeShowFormEvent(form);
        form->show();
//        afterShowFormEvent(form);
    }
}


void Essence::hide()
{
    if (opened && form != 0)
    {

        if (form->getFormWidget()->isVisible())
            beforeHideFormEvent(form);
        form->hide();
        afterHideFormEvent(form);

//        app->setActiveWindow(activeWidget);
    }
}


void Essence::view()
{
    if (form != 0)
    {
        form->getFormWidget()->setFocus(Qt::OtherFocusReason);
    }
}


bool Essence::open()
{
    if (Table::open())
    {
        setOrderClause();
        if (!app->isScriptMode())       // Если мы работаем не в скриптовом режиме, то создадим форму для этой сущности
            initForm();
        return true;
    }
    return false;
}


void Essence::close()
{
    if (m_networkAccessManager != 0)
        delete m_networkAccessManager;
    if (form != 0)
    {
        closeFormEvent(form);
        form->close();
        delete form;
    }
    closeScriptEngine();
    Table::close();
}


void Essence::setScriptEngine()
{
//    if (scriptEngine != 0)
//        delete scriptEngine;
    scriptEngine = new ScriptEngine(this);
}


void Essence::evaluateEngine()
{
    if (scriptEngineEnabled && scriptEngine != 0)
    {
        if (!scriptEngine->open(scriptFileName) || !scriptEngine->evaluate())
        {
            scriptEngineEnabled = false;
        }
    }
}


ScriptEngine* Essence::getScriptEngine()
{
    return scriptEngine;
}


void Essence::openScriptEngine()
{
    if (scriptEngineEnabled && db->isFileExist(scriptFileName, ScriptFileType))
    {
        setScriptEngine();
        evaluateEngine();
        if (dictionaries != 0 && dictionaries->getDocument() != 0 && scriptEngine != 0)          // Если этот справочник является частью документа
            scriptEngine->setIsDocumentScript(true);                                             // То обозначим контекст выполнения скриптов

        initFormEvent(form);
    }
}


void Essence::closeScriptEngine()
{
    if (scriptEngine != 0)
    {
        scriptEngine->close();
        delete scriptEngine;
        scriptEngine = 0;
    }
}


void Essence::setEnabled(bool en)
{
    QString disabledMessage = QObject::trUtf8(" - изменения запрещены");
    enabled = en;
    if (scriptEngine != 0)
        scriptEngine->eventSetEnabled(en);
    if (enabled)
        form->getFormWidget()->setWindowTitle(form->getFormWidget()->windowTitle().remove(disabledMessage));
    else
    {
        if (!form->getFormWidget()->windowTitle().contains(disabledMessage))
            form->getFormWidget()->setWindowTitle(form->getFormWidget()->windowTitle().append(disabledMessage));
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
    form->getFormWidget()->setWindowTitle(title);
}


QString Essence::getFormTitle()
{
    return form->getFormWidget()->windowTitle();
}


bool Essence::isFormSelected()
{
    return form->isFormSelected();
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


void Essence::initFormEvent(Form* form)
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


void Essence::afterRowChanged()
{
    if (scriptEngineEnabled && getScriptEngine() != 0)
        getScriptEngine()->eventAfterRowChanged();
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
    QString command = preparedSelectCurrentRow.executedQuery();
    if (command.size() > 0)
    {
        if (preparedSelectCurrentRow.exec())
        {
            if (preparedSelectCurrentRow.first())
            {
                QModelIndex index = grdTable->currentIndex();
                for (int i = 0; i < preparedSelectCurrentRow.record().count(); i++)
                {
                    QString fieldName = preparedSelectCurrentRow.record().fieldName(i).toUpper();
                    QVariant value = preparedSelectCurrentRow.record().value(fieldName);
                    if (value != tableModel->record(index.row()).value(fieldName))
                        tableModel->setData(tableModel->index(index.row(), i), value, true);
                }
                grdTable->setCurrentIndex(index);
            }
        }
        else
            if (!preparedSelectCurrentRow.isValid())
            {
                TApplication::debug(1, QString("PreparedQuery Error: %1").arg(preparedSelectCurrentRow.lastError().text()));
                TApplication::debug(1, QString("PreparedQuery Expression: %1").arg(command));
            }
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
                reportScriptEngine->getReportContext()->setValue(QString("таблица%1.%2").arg(i).arg(field).toLower(), rec.value(field));
            }
            reportScriptEngine->getReportContext()->setValue(QString("таблица%1.%2").arg(i).arg("номерстроки"), QVariant(i));
        }
    }
}


void Essence::appendPrintValues(QString prefix, QSqlQuery* query)
{
    if (reportScriptEngine != 0)
    {
        int i = 1;
        query->first();
        while (query->isValid())
        {
            QSqlRecord rec = query->record();
            for (int j = 0; j < query->record().count(); j++)
            {
                reportScriptEngine->getReportContext()->setValue(QString("%1%2.%3").arg(prefix).arg(i).arg(query->record().fieldName(j)).toLower(), rec.value(j));
            }
            reportScriptEngine->getReportContext()->setValue(QString("%1%2.%3").arg(prefix).arg(i).arg("номерстроки"), QVariant(i));
            query->next();
            i++;
        }
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
        QDateTime locFileTime = QFileInfo(file).lastModified().addSecs(app->getSecDiff());  // Время модификации локального файла, приведенное к серверному времени
        QDateTime servFileTime = db->getFileDateTime(fileName, type);
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray array = file.readAll();
            file.close();
            qulonglong localFileCheckSum = db->calculateCRC32(&array);
            if (db->getFileCheckSum(fileName, type) != localFileCheckSum)
            {   // контрольные суммы файлов не совпадают или нужно сохранить принудительно
                if (app->isSA() && (!servFileTime.isValid() || servFileTime.secsTo(locFileTime) > 5))   // Если не указано время сохранения файла на сервере
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
        oldValues.insert(field.toUpper(), getValue(field));
    }
}


void Essence::restoreOldValues()
{
    foreach (QString fieldName, oldValues.keys())
    {
        setValue(fieldName, oldValues.value(fieldName));
    }
}


void Essence::keyboardReaded(QString barCode)
{
    if (scriptEngine != 0 && enabled)
        scriptEngine->eventBarCodeReaded(barCode);
}


void Essence::cardCodeReaded(QString cardCode)
{
    if (scriptEngine != 0 && enabled)
        scriptEngine->eventCardCodeReaded(cardCode);
}


void Essence::print(QString fileName)
// fileName - файл с шаблоном документа
{
    // Подготовим контекст для печати
    QHash<QString, QVariant> printValues;

    // Найдем полный путь к файлам с шаблонами
    QString fullFileName = app->getReportsPath();

    // Если нет каталога с отчетами, то создадим его
    if (!QDir(fullFileName).exists())
        QDir().mkpath(fullFileName);

    fullFileName += fileName;

    // Если такого шаблона нет, попробуем получить его с сервера
    getFile(app->getReportsPath(), fileName, ReportTemplateFileType);
    if (QDir().exists(fullFileName))
    {
        bool result = true;                         // По умолчанию документ будет печататься
        // Создадим скриптовый обработчик контекста печати
        DocumentScriptEngine scriptEngine(&printValues, this);
        reportScriptEngine = &scriptEngine;

        // Заполним контекст данными
        preparePrintValues();

        if (scriptEngine.open(fileName + ".js"))    // Если имеются скрипты, то запустим их и получим результат
        {
            result = scriptEngine.evaluate();       // Если скрипты вернут отрицательный результат, то документ не напечатается
        }

        if (result)
        {
            // Скопируем шаблон во временный файл
            QString ext = QFileInfo(fileName).suffix();
            QString tmpFileName = QDir::tempPath() + "/qt_temp_XXXXXX." + ext;

            QTemporaryFile templateFile(tmpFileName);
            if (templateFile.open())
            {
                tmpFileName = templateFile.fileName();
                templateFile.close();
                templateFile.remove();

                // Скопируем файл отчета (шаблон) во временный файл
                if (QFile().copy(fullFileName, tmpFileName))
                {
                    // На 3 секунды выведем сообщение об открытии документа
                    app->showMessageOnStatusBar(trUtf8("Открывается документ: ") + fileName, 3000);

                    // Из пользовательских настроек выберем обработчик шаблона
                    switch (app->getReportTemplateType())
                    {
                        // Обработчик шаблона запускает OpenOffice, для которого нужны специально подготовленные шаблоны с внутренними функциями
                        case OOreportTemplate:
                            {
                                OOReportEngine* report = new OOReportEngine(&scriptEngine);
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
                                OOXMLReportEngine* report = new OOXMLReportEngine(&scriptEngine);
                                if (report->open())
                                {
                                    report->open(tmpFileName, &printValues);
                                    report->close();
                                }
                                delete report;
                            }
                            break;
                        // Обработчик шаблона с подключение проекта OpenRPT, который предлагал Drake. С его уходом ветка умерла.
                        case OpenRPTreportTemplate:
                            {   // в пользовательских настройках стоит использовать ОО в качестве движка печати
//                               OpenRPTreportEngine report(&printValues, file, ext);
//                           report.open();
                            }
                            break;
                    }
                }
            }
        }
        reportScriptEngine = 0;
    }
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
