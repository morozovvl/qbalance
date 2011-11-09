#include <QTreeWidgetItem>
#include <QFrame>
#include <QDebug>
#include <QSizePolicy>
#include "configform.h"
#include "../kernel/app.h"

ConfigForm::ConfigForm(QObject* parent/* = NULL*/): Form(parent)
{
}


bool ConfigForm::open(QWidget* pwgt) {
    if (Form::open(pwgt)) {
        formWidget->setWindowTitle(QObject::trUtf8("Настройки"));

        QTreeWidget* treeWidget = new QTreeWidget();
        QTreeWidgetItem* treeWidgetItem0 = 0;
        QTreeWidgetItem* treeWidgetItem1 = 0;

        treeWidgetItem0 = new QTreeWidgetItem(treeWidget, QStringList(QObject::trUtf8("Справочники")));
        treeWidgetItem1 = new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Добавить") << "10");
        treeWidgetItem1 = new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Свойства") << "11");
        treeWidgetItem1 = new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Столбцы") << "12");
        treeWidgetItem1 = new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Доступ") << "13");

        treeWidgetItem0 = new QTreeWidgetItem(treeWidget, QStringList(QObject::trUtf8("Операции")));
        treeWidgetItem1 = new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Добавить") << "20");
        treeWidgetItem1 = new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Свойства") << "21");
        treeWidgetItem1 = new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Столбцы") << "22");
        treeWidgetItem1 = new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Доступ") << "23");

        treeWidgetItem0 = new QTreeWidgetItem(treeWidget, QStringList(QObject::trUtf8("Отчеты")));
        treeWidgetItem1 = new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Свойства") << "30");
        treeWidgetItem1 = new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Столбцы") << "31");
        treeWidgetItem1 = new QTreeWidgetItem(treeWidgetItem0, QStringList() << QObject::trUtf8("Доступ") << "32");
        connect(treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(dispatch(QTreeWidgetItem*, int)));
        treeWidget->setHeaderHidden(true);
        treeWidget->setSortingEnabled(false);
        treeWidget->setFixedWidth(200);

        frame = new QFrame();
        frame->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
        frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->addWidget(treeWidget);
        hLayout->addWidget(frame);
        QVBoxLayout* vbxLayout = qFindChild<QVBoxLayout*>(formWidget, "vbxLayout");
        if (vbxLayout != 0) {
            vbxLayout->insertLayout(0, hLayout);
        }
        readSettings();
        setIcons();
        return true;
    }
    return false;
}


void ConfigForm::close() {
    Form::close();
    writeSettings();
}


void ConfigForm::dispatch(QTreeWidgetItem* item, int) {
    switch(item->text(1).toInt()) {
    case 10: dictAdd();
                break;
    case 11: dictProperties();
                break;
    case 12: dictColumns();
                break;
    case 13: dictPermissions();
                break;
    }
}


void ConfigForm::dictAdd() {
    QLayout* layout = frame->layout();
    if (layout != 0) {
        delete layout;
    }
    QGridLayout* vLayout = new QGridLayout();
    QLabel* lblTableName = new QLabel(QObject::trUtf8("Наименование таблицы:"));
    lblTableName->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QLineEdit* lnEdit = new QLineEdit();
    lnEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    vLayout->addWidget(lblTableName, 0, 0, Qt::AlignRight);
    vLayout->addWidget(lnEdit, 0, 1, Qt::AlignRight);
    frame->setLayout(vLayout);
    qDebug() << "dictAdd()";
}


void ConfigForm::dictProperties() {
    QLayout* layout = frame->layout();
    if (layout != 0) {
        delete layout;
    }
    qDebug() << "dictProperties()";
}


void ConfigForm::dictColumns() {
    QLayout* layout = frame->layout();
    if (layout != 0) {
        delete layout;
    }
    qDebug() << "dictColumns()";
}


void ConfigForm::dictPermissions() {
    QLayout* layout = frame->layout();
    if (layout != 0) {
        delete layout;
    }
    qDebug() << "dictPermissions()";
}


