#include "adddictionarywizard.h"
#include "../kernel/app.h"

AddDictionaryWizard::AddDictionaryWizard(): WizardForm()
  , tableName(NULL)
  , tableMenuName(NULL)
{
}


void AddDictionaryWizard::initFrames()
{
    // Добавим фреймы
    QFrame* frame = 0;
    frame = new QFrame(formWidget);
    frame->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QGridLayout* layout = new QGridLayout(frame);
    QLabel* lblTableName = new QLabel(QObject::trUtf8("Наименование на сервере:"), frame);
    tableName = new QLineEdit(frame);
    layout->addWidget(lblTableName, 0, 0, Qt::AlignRight);
    layout->addWidget(tableName, 0, 1, Qt::AlignLeft);

    QLabel* lblMenuTableName = new QLabel(QObject::trUtf8("Наименование в меню:"), frame);
    tableMenuName = new QLineEdit(frame);
    layout->addWidget(lblMenuTableName, 1, 0, Qt::AlignRight);
    layout->addWidget(tableMenuName, 1, 1, Qt::AlignLeft);

    QLabel* lblMenu = new QLabel(QObject::trUtf8("Доступен в меню:"), frame);
    chbMenu = new QCheckBox(frame);
    layout->addWidget(lblMenu, 2, 0, Qt::AlignRight);
    layout->addWidget(chbMenu, 2, 1, Qt::AlignLeft);

    layout->setRowStretch(3, 1);
    layout->setColumnStretch(1, 1);
    qDebug() << frame->width();
    frame->setLayout(layout);
    addFrame(frame);

/*
    frame = new QFrame(formWidget);
    frame->setLayout(new QVBoxLayout());
    frame->layout()->addWidget(new QLabel(QObject::trUtf8("Фрейм 2")));
    addFrame(frame);
    frame = new QFrame(formWidget);
    frame->setLayout(new QVBoxLayout());
    frame->layout()->addWidget(new QLabel(QObject::trUtf8("Фрейм 3")));
    addFrame(frame);
*/
}


void AddDictionaryWizard::getData(QString tName)
{
    if (tName.size() > 0)
    {
        tableName->setText(tName);
        tableName->setEnabled(false);
        tableMenuName->setText(TApplication::exemplar()->getDictionaries()->getDictionaryTitle(tName));
    }
}


bool AddDictionaryWizard::execute()
{
    tableName->setText(tableName->text().trimmed());
    tableMenuName->setText(tableMenuName->text().trimmed());
    return TApplication::exemplar()->getDBFactory()->createNewDictionary(tableName->text(), tableMenuName->text(), chbMenu->isChecked());
}
