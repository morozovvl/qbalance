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

#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>
#include <QMap>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QMessageBox>
#include <QMenu>
#include <QUiLoader>
#include <QFile>
#include "essence.h"
#include "../kernel/app.h"
#include "../gui/form.h"
#include "../gui/formgridsearch.h"
#include "../gui/mainwindow.h"
#include "../report/reportengine.h"
#include "../report/ooreportengine.h"
#include "../report/openrptreportengine.h"
#include "../engine/reportscriptengine.h"
#include "../engine/reportcontext.h"


Essence::Essence(QString name, QObject *parent): Table(name, parent)
{
    form = 0;
    parentForm = 0;
    scriptEngine = 0;
    parentForm  = TApplication::exemplar()->getMainWindow()->centralWidget();
    formTitle   = "";
    lInsertable = false;
    lDeleteable = false;
    lViewable   = false;
    lUpdateable = false;
    lPrintable  = false;
    idFieldName = db->getObjectName("код");
    nameFieldName = db->getObjectName("имя");
    scriptEngine = 0;
    scriptFileName =  tableName + ".qs";
    connect(this, SIGNAL(showError(QString)), TApplication::exemplar(), SLOT(showError(QString)));
    photoPath = "";
    photoIdField = "";
}


Essence::~Essence() {
    disconnect(this, 0, 0, 0);
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
    bool lResult = true;
    if (scriptEngine != 0)
    {
        currentFieldName = tableModel->getFieldName(index.column());
        lResult = scriptEngine->evaluate();
    }
    if (lResult)
        lResult = tableModel->submit(index);
    else
        tableModel->revertAll();
    return lResult;
}


QVariant Essence::getValue(QString name, int row)
{
    QVariant result;
    if (row >= 0)
    {
        result =  tableModel->record(row).value(name);
    }
    else
    {
        int r = form->getCurrentIndex().isValid() ? form->getCurrentIndex().row() : 0;
        result = tableModel->record(r).value(name);
    }
    // ВНИМАНИЕ!!!
    // Не могу понять, почему тип поля "p1__кол" возвращается как QString. Должен быть double
    // Типы полей "p2__кол" и "p3__кол" возвращаются нормальные - double
    // пока не разобрался, почему это так - временно делаю следующее преобразование
    if (name == "p1__кол")
        result.convert(QVariant::Double);

    return result;
}


void Essence::setValue(QString name, QVariant value, int row)
{
    int r;
    if (row >= 0)
        r = row;
    else
    {
        r = form->getCurrentIndex().isValid() ? form->getCurrentIndex().row() : 0;
    }
    int col = tableModel->record().indexOf(name);
    tableModel->setData(tableModel->index(r, col), value);
    tableModel->submit(tableModel->index(r, col));
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
    for (int i = 0; i < tableModel->rowCount(); i++) {
        form->getGridTable()->selectRow(i);
        if (getId() == id) {
            form->setCurrentIndex(form->getCurrentIndex().sibling(i, 0));
            return;
        }
    }
    if (tableModel->rowCount() > 0)
    {
        QModelIndex index = form->getCurrentIndex();
        form->setCurrentIndex(index.sibling(0, 0));
    }
}


QString Essence::getPhotoFile()
{
    QString idField;    // Имя поля, в котором берем значение идентификатора фотографии.
    QString idValue;    // Значение идентификатора фотографии
    QString file;       // Полное имя файла с фотографией
    QString localFile;  // Локальный путь к фотографии
    QString fullFile;   // Полный путь к фотографии

    // Сначала получим имя поля из которого будем брать значение идентификатора
    if (photoIdField.size() == 0)
        // Если имя поля, из которого нужно брать идентификатор фотографии не установлено, то будем считать идентификатором код позиции
        idField = db->getObjectName("код");
    else
        idField = photoIdField;

    // Теперь получим значение идентификатора
    if (tableModel->rowCount() > 0)
        idValue = getValue(idField).toString().trimmed();

    if (idValue.size() > 0)
    {
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
        if (file.size() > 0)
        {
            file = file + "/" + idValue + ".jpg";
            localFile = file;       // Запомним локальный путь к фотографии на случай обращения к серверу за фотографией
            if (file.left(1) == "~")
            {   // Если путь к фотографиям является относительным пути к самой программе
                file.remove(0, 1);
                file = TApplication::exemplar()->applicationDirPath() + file;
            }
            fullFile = file;
            if (!QDir().exists(file))
               file = "";              // Локальный файл с фотографией не существует
        }
        if (file.size() == 0)
        {   // Локальный файл с фотографией не найден, попробуем получить фотографию с сервера
            if (localFile.size() > 0)
            {   // Если мы знаем, под каким именем искать фотографию на нашем сервере, то попробуем обратиться к нему за фотографией
                QByteArray picture = db->getFile(localFile, PictureFileType);
                qDebug() << picture.size();
                if (picture.size() > 0)
                {   // Если удалось получить какую-то фотографию
                    savePicture(fullFile, &picture);
                    if (QDir().exists(fullFile))
                        file = fullFile;
                }
            }
            if (file.size() == 0)
            {   // Фотография не найдена на сервере, попробуем получить фотографию из Интернета
                file = preparePictureUrl();
                // Если в скриптах указано, откуда брать фотографию
                if (file.left(4) == "http" && photoPath.size() > 0)  // Имя файла - это адрес в интернете, и указано, куда этот файл будет сохраняться
                {
                    QUrl url(file);
                    urls.insert(QString("%1:%2%3").arg(url.host()).arg(url.port()).arg(url.path()), idValue);             // Запомним URL картинки и его локальный код
                    QNetworkRequest request(url);
                    if (url.isValid())
                    {
                        if (m_networkAccessManager == 0)
                        {
                            m_networkAccessManager = new QNetworkAccessManager(this);
                            connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
                        }
                        m_networkAccessManager->get(request);   // Запустим скачивание картинки
                    }
                    else
                        file = "";
                }
            }
        }
        else
        {   // Локальный файл с фотографией найден. Проверим, имеется ли он на сервере и если что, то сохраним его там
            if (!db->isFileExist(localFile, PictureFileType))
            {
                QFile file(fullFile);
                if (file.open(QIODevice::ReadOnly))
                {
                    db->setFile(localFile, PictureFileType, file.readAll());
                    file.close();
                }
            }
        }
    }
    return file;
}


void Essence::replyFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        // Данные с фотографией получены, запишем их в файл
        QString url = QString("%1:%2%3").arg(reply->url().host()).arg(reply->url().port()).arg(reply->url().path());
        QString idValue = urls.value(url);
        if (idValue.size() > 0)
        {
            QByteArray array = reply->readAll();
            savePicture(photoPath + "/" + idValue + ".jpg", &array);
            urls.remove(url);
        }
    }
}


void Essence::savePicture(QString file, QByteArray* array)
{
    QFile pictFile(file);
    if (pictFile.open(QIODevice::WriteOnly))
    {
        pictFile.write(*array);
        pictFile.close();
    }
}


bool Essence::add()
{
    return false;
}


bool Essence::remove()
{
    if (TApplication::exemplar()->getGUIFactory()->showYesNo("Удалить запись? Вы уверены?") == QMessageBox::Yes)
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
    if (opened && form != 0) {
        return form->exec();
    }
    return 0;
}

void Essence::show()
{
    if (!opened) open();
    if (opened && form != 0) {
        form->show();
    }
}


void Essence::hide()
{
    if (opened && form != 0) {
        form->hide();
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
        initForm();
        setScriptEngine();
        if (scriptEngine != 0)
        {
            if (!scriptEngine->open(scriptFileName))
                return false;
            if (!scriptEngine->evaluate())
                return false;
        }
        initFormEvent();
        return true;
    }
    return false;
}


void Essence::close()
{
    if (form != 0)
    {
        closeFormEvent();
        form->writeSettings();
        form->close();
    }
    delete scriptEngine;
    delete form;
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


ScriptEngine* Essence::getScriptEngine()
{
    return scriptEngine;
}


void Essence::initForm() {
    setForm();
    form->setIcons();
    form->readSettings();
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


bool Essence::isFormSelected() {
    return form->selected();
}


void Essence::cmdOk() {
}


void Essence::cmdCancel() {
}


void Essence::initFormEvent() {
    if (getScriptEngine() != 0) {
        getScriptEngine()->eventInitForm(form);
    }
}


void Essence::beforeShowFormEvent() {
    if (getScriptEngine() != 0) {
        getScriptEngine()->eventBeforeShowForm(form);
    }
}


void Essence::afterHideFormEvent() {
    if (getScriptEngine() != 0)
        getScriptEngine()->eventAfterHideForm(form);
}


void Essence::closeFormEvent() {
    if (getScriptEngine() != 0) {
        getScriptEngine()->eventCloseForm(form);
    }
}


QString Essence::preparePictureUrl()
{
    QString result;
    if (getScriptEngine() != 0) {
        result = getScriptEngine()->preparePictureUrl(this);
    }
    return result;
}


void Essence::preparePrintValues(ReportScriptEngine* reportEngine)
{   // Зарядим константы в контекст печати
    QString constDictionaryName = db->getObjectName("константы");
    QString constNameField = db->getObjectName(constDictionaryName + ".имя");
    QString constValueField = db->getObjectName(constDictionaryName + ".значение");
    // Откроем справочник констант
    TApplication::exemplar()->getDictionaries()->addDictionary(db->getObjectName(constDictionaryName));
    if (TApplication::exemplar()->getDictionaries()->isMember(constDictionaryName))
    {
        Dictionary* dict = TApplication::exemplar()->getDictionaries()->getDictionary(constDictionaryName);
        dict->query();    // Прочитаем содержимое справочника констант
        QSqlTableModel* model = dict->getTableModel();
        for (int i = 0; i < model->rowCount(); i++)
        {
            QSqlRecord rec = model->record(i);
            reportEngine->getReportContext()->setValue(QString("%1.%2").arg(constDictionaryName).arg(rec.value(constNameField).toString()), rec.value(constValueField));
        }
    }
}


void Essence::print(QString file)
{
    // Подготовим данные для печати
    QMap<QString, QVariant> printValues;
    ReportScriptEngine scriptEngine(&printValues);
    preparePrintValues(&scriptEngine);
    QString ext = TApplication::exemplar()->getReportTemplateExt();
    if (scriptEngine.open(file + "." + ext + ".qs") && scriptEngine.evaluate())
    {
        switch (TApplication::exemplar()->getReportTemplateType())
        {
            case OOreportTemplate:
                {   // в пользовательских настройках стоит использовать ОО в качестве движка печати
                    OOReportEngine report(&printValues, file, ext);
                    report.open();
                }
                break;
            case OpenRPTreportTemplate:
                {   // в пользовательских настройках стоит использовать ОО в качестве движка печати
//                    OpenRPTreportEngine report(&printValues, file, ext);
//                    report.open();
                }
                break;
        }
    }
}

