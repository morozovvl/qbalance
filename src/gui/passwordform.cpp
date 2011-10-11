#include <QComboBox>
#include <QLineEdit>
#include <QFormLayout>
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
        LoginSelector = new QComboBox;
        PasswordEditor = new QLineEdit;
        PasswordEditor->setEchoMode(QLineEdit::Password);

        QFormLayout* layout = new QFormLayout;

        layout->addRow(tr("Логин:"), LoginSelector);
        layout->addRow(tr("Пароль:"), PasswordEditor);

        QVBoxLayout* vbxLayout = qFindChild<QVBoxLayout*>(formWidget, "vbxLayout");
        if (vbxLayout != 0)
            vbxLayout->insertLayout(0, layout);
        return true;
    }
    return false;
}


void PassWordForm::addLogin(QString login) {
        LoginSelector->addItem(login);
        LoginSelector->setCurrentIndex(0);
        LoginSelector->repaint();
;	}

void PassWordForm::addLogin(QStringList list) {
        LoginSelector->addItems(list);
        LoginSelector->setCurrentIndex(0);
        LoginSelector->repaint();
        }

void PassWordForm::cmdOk() {
    Form::cmdOk();
    login = LoginSelector->currentText();
    password = PasswordEditor->text();
    writeSettings();
}

int PassWordForm::exec() {
    readSettings();
    Form::setIcons();
    return Form::exec();
}

void PassWordForm::readSettings() {
    QSettings settings;
    if (settings.status() == QSettings::NoError) {
        QString user = settings.value("defaultUser").toString();
        if (user.size() > 0)
            LoginSelector->setCurrentIndex(LoginSelector->findText(user));
    }
}

void PassWordForm::writeSettings() {
    QSettings settings;
    if (settings.status() == QSettings::NoError) {
        settings.setValue("defaultUser", login);
    }
}
