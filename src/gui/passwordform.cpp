#include <QComboBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QStringList>

#include "passwordform.h"

PassWordForm::PassWordForm(QObject* parent/* = NULL*/)
: Form(parent)
{
}

bool PassWordForm::open(QWidget* pwgt/* = 0*/)
// Создает форму ввода пароля на основе формы с кнопками "Ок" и "Cancel"
{
    if (Form::open(pwgt))
    {
	pcmbLogin = new QComboBox;
	ptxtPassword = new QLineEdit;
	ptxtPassword->setEchoMode(QLineEdit::Password);

        QLabel* plblLogin = new QLabel(tr("Логин:"));
        QLabel* plblPassword = new QLabel(tr("Пароль:"));

	QGridLayout* ptopLayout = new QGridLayout;
	ptopLayout->addWidget(plblLogin, 0, 0, Qt::AlignRight);
	ptopLayout->addWidget(plblPassword, 1, 0, Qt::AlignRight);
	ptopLayout->addWidget(pcmbLogin, 0, 1);
	ptopLayout->addWidget(ptxtPassword, 1, 1);

        QVBoxLayout* vbxLayout = qFindChild<QVBoxLayout*>(formWidget, "vbxLayout");
        if (vbxLayout != 0)
            vbxLayout->insertLayout(0, ptopLayout);
        return true;
    }
    return false;
}


void PassWordForm::addLogin(QString login) {
	pcmbLogin->addItem(login);
        pcmbLogin->setCurrentIndex(pcmbLogin->currentIndex());
	}

void PassWordForm::addLogin(QStringList list) {
	pcmbLogin->addItems(list);
	}

void PassWordForm::cmdOk() {
    Form::cmdOk();
    login = pcmbLogin->currentText();
    password = ptxtPassword->text();
    writeSettings();
}

int PassWordForm::doExec() {
    readSettings();
    return Form::doExec();
}

void PassWordForm::readSettings() {
    QSettings settings;
    if (settings.status() == QSettings::NoError) {
        QString user = settings.value("defaultUser").toString();
        if (user.size() > 0)
            pcmbLogin->setCurrentIndex(pcmbLogin->findText(user));
    }
}

void PassWordForm::writeSettings() {
    QSettings settings;
    if (settings.status() == QSettings::NoError) {
        settings.setValue("defaultUser", login);
    }
}
