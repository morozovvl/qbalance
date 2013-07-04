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
#include <QtCore/QMap>
#include <QtCore/QDir>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtGui/QMessageBox>
#include <QtGui/QMenu>
#include <QtCore/QFile>
#include <QtCore/QTemporaryFile>
#include <QDebug>
//#include <boost/crc.hpp>
#include "essence.h"
#include "../kernel/app.h"
#include "../gui/form.h"
#include "../gui/formgridsearch.h"
#include "../gui/mainwindow.h"
#include "../report/reportengine.h"
#include "../report/ooreportengine.h"
//#include "../report/oounoreportengine.h"
#include "../report/ooxmlreportengine.h"
#include "../engine/reportscriptengine.h"
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
    idFieldName = db->getObjectName("код");
    nameFieldName = db->getObjectName("имя");
    scriptEngine = 0;
    scriptFileName =  tableName + ".qs";
    scriptEngineEnabled = true;                 // По умолчанию разрешена загрузка скриптового движка
    photoPath = "";
    photoIdField = "";
    photoEnabled = false;
    m_networkAccessManager = 0;
    m_request = 0;
    doSubmit = false;                           // По умолчанию не обновлять записи автоматически
    defaultFilter = "";
}


Essence::~Essence() {
    this->disconnect();
}


Dialog* Essence::getFormWidget() {
    if (!opened)
    {
        open();
    }
    return form->getForm();
}


bool Essence::calculate(const QModelIndex &index)
{
    if (scriptEngine != 0)
    {
        currentFieldName = tableModel->getFieldName(index.column());
        scriptEngine->eventCalcTable();
        scriptEngine->eventAfterCalculate();
        if (scriptEngine->getErrorMessage().size() > 0)
        {
            app->showError(scriptEngine->getErrorMessage());
            scriptEngine->setErrorMessage("");
        }
        if (!scriptEngine->getScriptResult())
        {
            return false;
        }
    }
    return true;
}


QVariant Essence::getValue(QString n, int row)
{
    QVariant result;
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
            int r = form->getCurrentIndex().isValid() ? form->getCurrentIndex().row() : 0;
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
    return result;
}


void Essence::setValue(QString n, QVariant value, int row)
{
    QString name = n.toUpper();
    int fieldColumn = tableModel->fieldIndex(n);
    if (fieldColumn >= 0)
    {
        QModelIndex index, oldIndex;

        if (row >= 0)
            oldIndex = form->getCurrentIndex();

        index = tableModel->index((row >= 0 ? row : form->getCurrentIndex().row()), fieldColumn);
        tableModel->setData(index, value);

        if (doSubmit)
        {
            if (getValue(name) != getOldValue(name))    // Для экономии трафика и времени посылать обновленные данные на сервер будем в случае, если данные различаются
                tableModel->submit(index);
        }

        if (row >= 0)
            form->setCurrentIndex(oldIndex);
    }
    else
        app->showError(QObject::trUtf8("Не существует колонки ") + n);
}


qulonglong Essence::getId(int row)
{
    if (row >= 0)
        return getValue(idFieldName, row).toULongLong();
    int r = form->getCurrentIndex().isValid() ? form->getCurrentIndex().row() : 0;
    return getValue(idFieldName, r).toULongLong();
}


QString Essence::getName(int row)
{
    if (row >= 0)
        return getValue(nameFieldName, row).toString();
    int r = form->getCurrentIndex().isValid() ? form->getCurrentIndex().row() : 0;
    return getValue(nameFieldName, r).toString();
}


void Essence::setId(qulonglong id)
{
    query(QString("\"%1\".\"%2\"=%3").arg(tableName).arg(db->getObjectName("код")).arg(id));
}


void Essence::query(QString filter)
{
    if (filter.size() > 0 && defaultFilter.size() > 0)
    {
        Table::query(filter + " AND " + defaultFilter);
        return;
    }
    if (defaultFilter.size() > 0)
    {
        Table::query(defaultFilter);
        return;
    }
    Table::query(filter);
 }


QString Essence::getPhotoPath()
{
    QString file;
    // Попробуем получить локальный путь к фотографии
    if (photoPath.size() == 0)
    {
        // Если путь, откуда нужно брать фотографии не установлен, то установим его по умолчанию для данного справочника
        file = db->getDictionaryPhotoPath(tableName);
    }
    else
    {
        file = photoPath;
    }
    return file;
}


QString Essence::getPhotoFile()
{
    QString idValue;    // Значение идентификатора фотографии
    QString file;       // Полное имя файла с фотографией
    QString localFile;  // Локальный путь к фотографии
    QString fullFileName;   // Полный путь к фотографии
    QString pictureUrl;

    if (photoEnabled)
    {
        pictureUrl = preparePictureUrl();

        // Сначала получим имя поля из которого будем брать значение идентификатора
        if (photoIdField.size() == 0 && isDictionary)
        {
            // Если имя поля, из которого нужно брать идентификатор фотографии не установлено, то будем считать идентификатором код позиции
            photoIdField = db->getObjectName("код");
        }

        // Теперь получим значение идентификатора
        if (tableModel->rowCount() > 0 && photoIdField.size() > 0)
        {
            int id = getValue(photoIdField).toInt();
            if (id != 0)
            {
                idValue = QString("%1").arg(id).trimmed();
                file = getPhotoPath();
                if (file.size() > 0)
                {
                    photoPath = file;
                    localFile = file;       // Запомним локальный путь к фотографии на случай обращения к серверу за фотографией
                    if (file.left(1) == "~")
                    {   // Если путь к фотографиям является относительным пути к самой программе
                        file.remove(0, 1);
                        file = app->applicationDirPath() + file;
                    }
                    fullFileName = file;
                    // Если каталога с картинками нет, то попытаемся его создать
                    if (!QDir(fullFileName).exists())
                        QDir().mkpath(fullFileName);
                    file = "/" + idValue + ".jpg";
                    localFile += file;
                    fullFileName += file;
                    file = fullFileName;
                    if (!QDir().exists(file))
                        file = "";              // Локальный файл с фотографией не существует
                    if (isDictionary)
                    {
                        if (file.size() == 0)
                        {   // Локальный файл с фотографией не найден, попробуем получить фотографию с нашего сервера. Будем делать это только для справочника, а не для документа
                            if (localFile.size() > 0)
                            {   // Если мы знаем, под каким именем искать фотографию на нашем сервере, то попробуем обратиться к нему за фотографией
                                if (db->getFileCheckSum(localFile, PictureFileType, true) != 0)
                                {
                                    app->showMessageOnStatusBar(tr("Запущена загрузка с сервера фотографии с кодом ") + QString("%1").arg(idValue), 3000);
                                    QByteArray picture = db->getFile(localFile, PictureFileType, true); // Получить файл с картинкой из расширенной базы
                                    if (picture.size() > 0)
                                    {   // Если удалось получить какую-то фотографию
                                        saveFile(fullFileName, &picture);
                                        if (QDir().exists(fullFileName))
                                            file = fullFileName;
                                    }
                                }
                            }
                            if (file.size() == 0)
                            {   // Фотография не найдена на сервере, попробуем получить фотографию из Интернета
                                file = pictureUrl;
                                // Если в скриптах указано, откуда брать фотографию
                                if (file.left(4) == "http" && photoPath.size() > 0)  // Имя файла - это адрес в интернете, и указано, куда этот файл будет сохраняться
                                {
                                    QUrl url(file);
                                    if (url.isValid())
                                    {
                                        if (m_networkAccessManager == 0)
                                        {
                                            m_networkAccessManager = new QNetworkAccessManager(this);
                                            connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
                                        }
                                        urls.insert(QString("%1:%2%3").arg(url.host()).arg(url.port(80)).arg(url.path()), idValue);             // Запомним URL картинки и его локальный код
                                        m_request = new QNetworkRequest(url);
                                        m_networkAccessManager->get(*m_request);   // Запустим скачивание картинки
                                        app->showMessageOnStatusBar(tr("Запущена загрузка из Интернета фотографии с кодом ") + QString("%1").arg(idValue), 3000);
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
                                QFile file(fullFileName);
                                if (file.open(QIODevice::ReadOnly))
                                {
                                    QByteArray array = file.readAll();
                                    qulonglong localFileCheckSum = calculateCRC32(&array);
                                    qulonglong removeFileCheckSum = db->getFileCheckSum(localFile, PictureFileType, true);
                                    if (removeFileCheckSum != localFileCheckSum)    // контрольные суммы не совпадают, загрузим локальный файл в базу
                                                                                    // предполагается, что локальный файл свежее того, который в базе
                                    {
                                        db->setFile(localFile, PictureFileType, array, localFileCheckSum, true);      // Сохранить картинку в расширенную базу
                                    }
                                    file.close();
                                }
                            }
                        }
                    }
                }
                else
                    setPhotoEnabled(false);
            }
        }
    }
    return file;
}


void Essence::replyFinished(QNetworkReply* reply)
{
    QString url = QString("%1:%2%3").arg(reply->url().host()).arg(reply->url().port(80)).arg(reply->url().path());
    QString idValue = urls.value(url);
    if (reply->error() == QNetworkReply::NoError)
    {
        // Данные с фотографией получены, запишем их в файл
        if (idValue.size() > 0)
        {
            QString file = photoPath;
            if (file.left(1) == "~")
            {   // Если путь к фотографиям является относительным пути к самой программе
                file.remove(0, 1);
                file = app->applicationDirPath() + file;
            }
            QByteArray array = reply->readAll();
            saveFile(file + "/" + idValue + ".jpg", &array);
            urls.remove(url);
            app->showMessageOnStatusBar(tr("Загружена фотография с кодом ") + QString("%1").arg(idValue), 3000);

            // Проверим, не нужно ли обновить фотографию
            if (idValue == getValue(photoIdField).toString().trimmed())
                emit photoLoaded();
        }
    }
    else
    {
        urls.remove(url);
        app->showMessageOnStatusBar(tr("Не удалось загрузить фотографию с кодом ") + QString("%1").arg(idValue), 3000);
    }
}


void Essence::saveFile(QString file, QByteArray* array)
{
    QFile pictFile(file);
    if (pictFile.open(QIODevice::WriteOnly))
    {
        pictFile.write(*array);
        pictFile.close();
    }
}


bool Essence::remove()
{
    if (app->getGUIFactory()->showYesNo("Удалить запись? Вы уверены?") == QMessageBox::Yes)
    {
        return true;
    }
    return false;
}


int Essence::exec()
{
    if (!opened)
    {
        open();
    }
    if (opened && form != 0)
    {
        activeWidget = app->activeWindow();
        return form->exec();
    }
    return 0;
}


void Essence::show()
{
    if (!opened) open();
    if (opened && form != 0)
    {
        activeWidget = app->activeWindow();
        form->show();
        prepareSelectCurrentRowCommand();
    }
}


void Essence::hide()
{
    if (opened && form != 0)
    {
        form->hide();
        app->setActiveWindow(activeWidget);
    }
}


void Essence::view()
{
    if (form != 0)
        form->getForm()->setFocus(Qt::OtherFocusReason);
}


bool Essence::open()
{
    if (Table::open())
    {
        setOrderClause();
        setScriptEngine();
        return true;
    }
    return false;
}


void Essence::close()
{
    if (form != 0)
    {
        closeFormEvent();
        form->close();
        delete form;
    }
    if (scriptEngine != 0)
    {
//        scriptEngine->close();
//        delete scriptEngine;
    }
    Table::close();
}


void Essence::setForm()
{
    form = new FormGrid();
    form->open(parentForm, this);
    form->setButtonsSignals();
}


void Essence::setScriptEngine()
{
    scriptEngine = new ScriptEngine(this);
}


void Essence::evaluateEngine()
{
    if (scriptEngineEnabled && scriptEngine != 0)
    {
        if (!scriptEngine->open(scriptFileName) || !scriptEngine->evaluate())
        {
            if (scriptEngine->hasUncaughtException())
            {
                app->getGUIFactory()->showError(QString(QObject::trUtf8("Ошибка [%1] в строке %2 !")).arg(scriptEngine->uncaughtException ().toString())
                                                                                                  .arg(scriptEngine->uncaughtExceptionLineNumber()));
            }
            else
                app->getGUIFactory()->showError(QString(QObject::trUtf8("Не удалось загрузить скрипты!")));
            scriptEngineEnabled = false;
        }
    }
}


ScriptEngine* Essence::getScriptEngine()
{
    return scriptEngine;
}


void Essence::setEnabled(bool en)
{
    QString disabledMessage = QObject::trUtf8(" - изменения запрещены");
    enabled = en;
    if (scriptEngine != 0)
        scriptEngine->eventSetEnabled(en);
    if (enabled)
        form->getForm()->setWindowTitle(form->getForm()->windowTitle().remove(disabledMessage));
    else
    {
        if (!form->getForm()->windowTitle().contains(disabledMessage))
            form->getForm()->setWindowTitle(form->getForm()->windowTitle().append(disabledMessage));
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
    form->getForm()->setWindowTitle(title);
}


QString Essence::getFormTitle()
{
    return form->getForm()->windowTitle();
}


bool Essence::isFormSelected()
{
    return form->selected();
}


void Essence::cmdOk()
{
}


void Essence::cmdCancel()
{
}


FormGrid* Essence::getForm()
{
    return form;
}


void Essence::initFormEvent()
{
    if (scriptEngineEnabled)
    {
        getScriptEngine()->eventInitForm(form);
    }
}


void Essence::beforeShowFormEvent()
{
    if (scriptEngineEnabled)
    {
        getScriptEngine()->eventBeforeShowForm(form);
    }
}


void Essence::afterShowFormEvent()
{
    if (scriptEngineEnabled)
        getScriptEngine()->eventAfterShowForm(form);
}


void Essence::beforeHideFormEvent()
{
    if (scriptEngineEnabled)
        getScriptEngine()->eventBeforeHideForm(form);
}


void Essence::afterHideFormEvent()
{
    if (scriptEngineEnabled)
        getScriptEngine()->eventAfterHideForm(form);
}


void Essence::closeFormEvent()
{
    if (scriptEngineEnabled)
        getScriptEngine()->eventCloseForm(form);
}


QString Essence::preparePictureUrl()
{
    QString result;
    if (scriptEngineEnabled)
    {
        result = getScriptEngine()->preparePictureUrl(this);
    }
    return result;
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
            TApplication::debug(QString("PreparedQuery: %1\n").arg(command));
            if (preparedSelectCurrentRow.first())
            {
                QModelIndex index = form->getCurrentIndex();
                for (int i = 0; i < preparedSelectCurrentRow.record().count(); i++)
                {
                    QString fieldName = preparedSelectCurrentRow.record().fieldName(i).toUpper();
                    QVariant value = preparedSelectCurrentRow.record().value(fieldName);
                    if (value != tableModel->record(index.row()).value(fieldName))
                        tableModel->setData(index.sibling(index.row(), i), value, true);
                }
            }
        }
        else
            if (!preparedSelectCurrentRow.isValid())
            {
                TApplication::debug(QString("PreparedQuery Error: %1\n").arg(preparedSelectCurrentRow.lastError().text()));
                TApplication::debug(QString("PreparedQuery Expression: %1\n").arg(command));
            }
    }
}


void Essence::preparePrintValues(ReportScriptEngine* reportEngine)
{   // Зарядим константы в контекст печати
    QString constDictionaryName = db->getObjectName("константы");
    QString constNameField = db->getObjectName(constDictionaryName + ".имя");
    QString constValueField = db->getObjectName(constDictionaryName + ".значение");
    // Откроем справочник констант
    app->getDictionaries()->addDictionary(db->getObjectName(constDictionaryName));
    if (app->getDictionaries()->isMember(constDictionaryName))
    {
        Dictionary* dict = app->getDictionaries()->getDictionary(constDictionaryName);
        dict->query();    // Прочитаем содержимое справочника констант
        MySqlRelationalTableModel* model = dict->getTableModel();
        for (int i = 0; i < model->rowCount(); i++)
        {
            QSqlRecord rec = model->record(i);
            reportEngine->getReportContext()->setValue(QString("%1.%2").arg(constDictionaryName).arg(rec.value(constNameField).toString().trimmed()).toLower(), rec.value(constValueField));
        }
    }
    // Отсортируем таблицу
    QStringList sortColumns;
/*
    foreach(QString field, getFieldsList())
    {
        if (field.right(5).toUpper() == "__ИМЯ")
        {
            // Найдем первую колонку, в которой хранится имя позиции
            sortColumns << field;
            break;
        }
    }
*/
    // Заполним список сортирования данными
    QMap<QString, int>  sortedStrings;
    int rowCountWidth = QString("%1").arg(getTableModel()->rowCount()).length();
    for (int i = 0; i < getTableModel()->rowCount(); i++)
    {
        QSqlRecord rec = getTableModel()->record(i);
        QString fields;
        foreach(QString field, sortColumns)
        {
            fields.append(rec.value(field).toString().trimmed() + " ");
        }
        sortedStrings.insert(fields + QString("%1").arg(i, rowCountWidth), i);
    }

    //    for (int i = 0; i < getTableModel()->rowCount(); i++)
    int i = 0;
    foreach (QString name, sortedStrings.keys())
    {
        QSqlRecord rec = getTableModel()->record(sortedStrings.value(name));
        foreach(QString field, getFieldsList())
        {
//            if (enabledFields.count() == 0 || enabledFields.contains(field))
                reportEngine->getReportContext()->setValue(QString("таблица%1.%2").arg(i+1).arg(field).toLower(), rec.value(field));
        }
        reportEngine->getReportContext()->setValue(QString("таблица%1.%2").arg(i+1).arg("номерстроки"), QVariant(i+1));
        i++;
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
            saveFile(fullFileName, &templateFile);
            result = true;
        }
    }
    else
    {   // файл существует локально
        QFile file(fullFileName);
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray array = file.readAll();
            file.close();
            qulonglong localFileCheckSum = calculateCRC32(&array);
            if (db->getFileCheckSum(fullFileName, type) != localFileCheckSum)
            {   // контрольные суммы файлов не совпадают
                if (app->isSA())
                    db->setFile(fileName, type, array, localFileCheckSum);      // Сохранить копию файла на сервере, если мы работаем как SA
                else
                {
                    QByteArray templateFile = db->getFile(fileName, type);
                    if (templateFile.size() > 0)
                    {   // Если удалось получить шаблон отчета, то сохраним его локально
                        saveFile(fullFileName, &templateFile);
                    }
                }
            }
            result = true;
        }
    }
    return result;
}


qulonglong Essence::calculateCRC32(QByteArray* array)
{
/*
    boost::crc_optimal<32, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true>  crc_ccitt2;
    for(int index = 0; index < array->length(); index++)
    {
      crc_ccitt2((*array)[index]);
    }
    return crc_ccitt2();
*/

//    unsigned int CRC32_function(unsigned char *buf, unsigned long len)

    unsigned long crc_table[256];
    unsigned long crc;
    char *buf = array->data();
    unsigned long len = array->count();

    for (int i = 0; i < 256; i++)
    {
        crc = i;
        for (int j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        crc_table[i] = crc;
    }

    crc = 0xFFFFFFFFUL;
    while (len--)
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
    return crc ^ 0xFFFFFFFFUL;
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


void Essence::print(QString fileName)
{
    bool defaultFile = false;
    // Подготовим данные для печати
    QMap<QString, QVariant> printValues;
    ReportScriptEngine scriptEngine(&printValues);
    preparePrintValues(&scriptEngine);


    QString fullFileName = app->getReportsPath();

    // Если нет каталога с отчетами, то создадим его
    if (!QDir(fullFileName).exists())
        QDir().mkpath(fullFileName);

    fullFileName += fileName;
    // Если такого шаблона нет, попробуем получить его с сервера
    if (getFile(app->getReportsPath(), fileName, ReportTemplateFileType))
    {
        if (scriptEngine.open(fullFileName + ".qs") && scriptEngine.evaluate())
        {
            QString tmpFileName;
            QString ext = QFileInfo(fileName).suffix();
            if (!defaultFile)
            {
                // Скопируем файл отчета (шаблон) во временный файл
                QTemporaryFile templateFile;
                templateFile.setFileTemplate("qt_temp_XXXXXX." + ext);
                templateFile.open();
                templateFile.close();
                tmpFileName = QDir().tempPath() + "/" + templateFile.fileName();
                QFile().copy(fullFileName, tmpFileName);
            }
            else
                tmpFileName = fullFileName;
            app->showMessageOnStatusBar(trUtf8("Открывается документ: ") + fileName, 3000);
            switch (app->getReportTemplateType())
            {
                case OOreportTemplate:
                    {   // в пользовательских настройках стоит использовать ОО в качестве движка печати
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
                case OpenRPTreportTemplate:
                    {   // в пользовательских настройках стоит использовать ОО в качестве движка печати
//                        OpenRPTreportEngine report(&printValues, file, ext);
//                        report.open();
                    }
                    break;
            }
        }
    }
}

