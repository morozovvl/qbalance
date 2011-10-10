#include <QIntValidator>
#include <QSettings>
#include <QStringList>
#include "connectionform.h"
#include "app.h"

bool ConnectionForm::open(QWidget* pwgt, Essence* par) {
    return Form::open(pwgt, par);
}


void ConnectionForm::initForm(QString hostName, QString dbName, int portNum, bool readSettings) {
    formWidget->setWindowTitle(tr("Параметры соединения"));
    QGridLayout* ptopLayout = new QGridLayout;
    QLabel* plblConnection = new QLabel(tr("Имя соединения:"));
    QLabel* plblHost = new QLabel(tr("Адрес сервера:"));
    QLabel* plblPort = new QLabel(tr("Номер порта:"));
    QLabel* plblDatabase = new QLabel(tr("Наименование БД:"));
    pcmbConnection = new QComboBox;
    if (readSettings)
        pcmbConnection->setEditable(true);
    connect(pcmbConnection, SIGNAL(activated(int)), this, SLOT(connectionChanged(int)));
    ptxtHost = new QLineEdit(hostName);
    QString port;
    port.setNum(portNum);
    ptxtPort = new QLineEdit(port);
    QIntValidator* validator = new QIntValidator(1, 65535, this);        // Разрешенный диапазон портов
    ptxtPort->setValidator(validator);
    ptxtDatabase = new QLineEdit(dbName);
    ptopLayout->addWidget(plblConnection, 0, 0, Qt::AlignRight);
    ptopLayout->addWidget(plblHost, 1, 0, Qt::AlignRight);
    ptopLayout->addWidget(plblPort, 2, 0, Qt::AlignRight);
    ptopLayout->addWidget(plblDatabase, 3, 0, Qt::AlignRight);
    ptopLayout->addWidget(pcmbConnection, 0, 1);
    ptopLayout->addWidget(ptxtHost, 1, 1);
    ptopLayout->addWidget(ptxtPort, 2, 1);
    ptopLayout->addWidget(ptxtDatabase, 3, 1);
    QVBoxLayout* vbxLayout = qFindChild<QVBoxLayout*>(formWidget, "vbxLayout");
    if (vbxLayout != 0) {
        vbxLayout->insertLayout(0, ptopLayout);
        QHBoxLayout* cmdButtonLayout = qFindChild<QHBoxLayout*>(formWidget, "cmdButtonLayout");
        if (cmdButtonLayout != 0) {
            QPushButton* buttonDelete = new QPushButton(tr("&Удалить"));
            buttonDelete->setObjectName("buttonDelete");
            connect(buttonDelete, SIGNAL(clicked()), this, SLOT(cmdDelete()));
            cmdButtonLayout->insertWidget(0, buttonDelete);
            QPushButton* cmdSave = new QPushButton(tr("&Сохранить"));
            cmdSave->setObjectName("buttonSave");
            connect(cmdSave, SIGNAL(clicked()), this, SLOT(cmdSave()));
            cmdButtonLayout->insertWidget(0, cmdSave);
        }
    }
    formWidget->setMinimumHeight(200);
    formWidget->setMinimumWidth(350);
    if (readSettings)
        readConnectionsList();
}

int ConnectionForm::exec(DBFactory* d) {
    bool lResult;
    db = d;
    readDefaultSettings();
    readSettings(pcmbConnection->itemText(pcmbConnection->currentIndex()));
    lResult = Form::exec();
    db->setHostName(ptxtHost->text());
    db->setDatabaseName(ptxtDatabase->text());
    db->setPort(ptxtPort->text().toInt());
    return lResult;
}

void ConnectionForm::cmdSave() {
    writeSettings();
}

void ConnectionForm::cmdDelete() {
    deleteSettings(pcmbConnection->currentText());
}

void ConnectionForm::cmdOk() {
    db->setHostName(ptxtHost->text());
    db->setPort(ptxtPort->text().toInt());
    db->setDatabaseName(ptxtDatabase->text());
    writeDefaultSettings();
    Form::cmdOk();
}

void ConnectionForm::connectionChanged(int index) {
    readSettings(pcmbConnection->itemText(index));
}

void ConnectionForm::readConnectionsList() {
    QSettings settings;
    if (settings.status() == QSettings::NoError) {
          settings.beginGroup(CONNECTION_GROUP_NAME);
          pcmbConnection->clear();
          foreach (QString connectionName, settings.childGroups())
              pcmbConnection->addItem(connectionName);
          readSettings(pcmbConnection->currentText());
    }
}

void ConnectionForm::readDefaultSettings() {
    QSettings settings;
    if (settings.status() == QSettings::NoError) {
        QString connection = settings.value("defaultConnection").toString();
        if (connection.size() > 0)
            pcmbConnection->setCurrentIndex(pcmbConnection->findText(connection));
    }
}

void ConnectionForm::writeDefaultSettings() {
    QSettings settings;
    if (settings.status() == QSettings::NoError) {
        settings.setValue("defaultConnection", pcmbConnection->currentText());
    }
}

void ConnectionForm::readSettings(QString connectionName) {
    QSettings settings;
    if (connectionName.size() > 0 && settings.status() == QSettings::NoError) {
        settings.beginGroup(CONNECTION_GROUP_NAME);
        settings.beginGroup(connectionName);
        ptxtHost->setText(settings.value("hostName").toString());
        ptxtPort->setText(QString("%1").arg(settings.value("portName").toInt()));
        ptxtDatabase->setText(settings.value("dbName").toString());
        settings.endGroup();
        settings.endGroup();
    }
}

void ConnectionForm::writeSettings() {
    QSettings settings;
    if (settings.status() == QSettings::NoError) {
        settings.setValue("defaultConnection", pcmbConnection->currentText());
        settings.beginGroup(CONNECTION_GROUP_NAME);
        settings.beginGroup(pcmbConnection->currentText());
        settings.setValue("hostName", ptxtHost->text());
        settings.setValue("portName", ptxtPort->text().toInt());
        settings.setValue("dbName", ptxtDatabase->text());
        settings.endGroup();
        settings.endGroup();
    }
}

void ConnectionForm::deleteSettings(QString connectionName) {
    QSettings settings;
    if (connectionName.size() > 0 && settings.status() == QSettings::NoError) {
          settings.beginGroup(CONNECTION_GROUP_NAME);
          settings.remove(connectionName);
          settings.endGroup();
          readConnectionsList();
    }
}

