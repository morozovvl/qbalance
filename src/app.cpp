#include <QDate>
#include <QMessageBox>
#include <QObject>
#include "app.h"
#include "dictionaries.h"
#include "documents.h"
#include "gui/guifactory.h"
#include "gui/passwordform.h"
#include "gui/formgrid.h"
#include "gui/mainwindow.h"

QString TApplication::MaxSumMask       = "9999999999.99";
QString TApplication::IdFieldName      = QObject::trUtf8("код");
QString TApplication::NameFieldName    = QObject::trUtf8("имя");
QFile*  TApplication::DebugFile        = new QFile(QDir::currentPath() + "/" + TApplication::debugFileName());
QTextStream* TApplication::DebugStream = new QTextStream(TApplication::DebugFile);
bool    TApplication::DebugMode        = false;
TApplication* TApplication::Exemplar   = NULL;

TApplication::TApplication(QApplication* application) {
    Application = application;
    Application->setOrganizationName(TApplication::name());
    Application->setApplicationName(TApplication::name());
    db  = new DBFactory();
    gui = new GUIFactory(db);

    if (!Exemplar)
    {
        Exemplar = this;
        TApplication::MaxSumMask = TApplication::MaxSumMask.replace(".", QApplication::keyboardInputLocale().decimalPoint());
    }
}

TApplication::~TApplication()
{

}

Documents* TApplication::getDocuments(int opNumber) {
    QString operName = QString("oper%1").arg(opNumber);
    if (!documents.contains(operName)) {             // Если справочник с таким именем не существует, то попробуем его создать
        Documents* doc = new Documents(opNumber);
        if (!doc->open())
            return NULL;
        documents.insert(operName, doc);
    }
    return documents[operName];
}


Dictionaries* TApplication::getDictionaries()
{
    return dictionaryList;
}


QVariant TApplication::getDictionaryProperty(QString dictName, const char* property)
{
    return dictionaryList->getDictionaryProperty(dictName, property);
}


QVariant TApplication::getToperProperty(int operNumber, QString property)
{
    return topersList->getToperProperty(operNumber, property);
}


bool TApplication::doOpen() {
    bool lResult = false;   // По умолчанию будем считать, что приложение открыть не удалось
    endDate = QDate::currentDate();
    beginDate = endDate.addDays(-31);
    if (gui->open()) {  // Попытаемся открыть графический интерфейс
        forever         // Будем бесконечно пытаться открыть базу, пока пользователь не откажется
        {
            int result = gui->openDB(); // Попытаемся открыть базу данных
            if (result == 0)
            {   // БД открыть удалось
                dictionaryList = new Dictionaries;
                topersList = new Topers;
                if (dictionaryList->open() && topersList->open())
                {   // Удалось открыть спосок справочников и типовых операций
                    db->getPeriod(beginDate, endDate);
                    gui->getMainWindow()->showPeriod();
                    lResult = true;     // Приложение удалось открыть
                    break;  // Выйдем из бесконечного цикла открытия БД
                }
            }
            else if (result == -2)
                {   // Произошла ошибка соединения с сервером
                QString errorText = db->getErrorText();
                showError(errorText);
                if (gui->showMessage(QObject::tr("Не удалось соединиться с базой данных (БД). Возможно БД отсутствует."),
                                     QObject::tr("Попытаться создать новую БД?")) == QMessageBox::Yes)
                    // Попытаемся создать новую БД
                    db->createNewDB(gui->getLastHostName(), gui->getLastDbName(), gui->getLastPort());
            }
            else if (result == -1)      // Пользователь нажал кнопку Отмена
                break;  // Выйдем из бесконечного цикла открытия БД
        }
    }
    return lResult;
}

void TApplication::doClose() {
    foreach(Documents* doc, documents) {
        doc->close();
    }
    dictionaryList->close();
    delete dictionaryList;
    topersList->close();
    delete topersList;
    gui->close();
    delete gui;
    db->close();
    delete db;
}

QString TApplication::getFormsPath(QString formName) {
    QString fileName = getHomePath() + "/forms" + "/" + formName;
    return fileName;
}

QString TApplication::encoding()
{
    QString result("UTF-8");
#ifdef Q_OS_WIN32
    if (QSysInfo::windowsVersion() != QSysInfo::WV_WINDOWS7)
        result = "Windows-1251";
#endif
    return result;
}

QTextCodec* TApplication::codec()
{
    return QTextCodec::codecForName(encoding().toLatin1());
}

bool TApplication::setDebugMode(const bool& value)
{
    bool result = true;
    if (value && !debugMode())
    {
        result = debugFile().open(QFile::WriteOnly | QFile::Append);
    }
    else if (!value && debugMode())
    {
        debugFile().close();
    }

    DebugMode = value;

    return result;
}

void TApplication::debug(const QString& value)
{
    if (debugMode())
    {
        TApplication::debugStream() << QDateTime::currentDateTime().toString(logTimeFormat()) << value;
    }
}

TApplication* TApplication::exemplar()
{
    return Exemplar;
}
