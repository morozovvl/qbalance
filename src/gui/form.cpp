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

#include <QObject>
#include <QTextStream>
#include <QFormBuilder>
#include <QResource>
#include <QUiLoader>
#include <QTextCodec>
#include <QList>
#include "form.h"
#include "../kernel/app.h"
#include "mainwindow.h"
#include "dialog.h"

class TApplication;

Form::Form(QObject* par/* = NULL*/): QObject(par)
{
    parent = 0;
    formWidget = 0;
    cmdButtonLayout = 0;
    vbxLayout = 0;
    buttonOk = 0;
    buttonCancel = 0;
    db = TApplication::exemplar()->getDBFactory();
}


Form::~Form()
{
/*
    buttonOk->deleteLater();
    buttonCancel->deleteLater();
    cmdButtonLayout->deleteLater();
    vbxLayout->deleteLater();
*/
}


bool Form::open(QWidget* pwgt, Essence* par, QString fName) {
    parent = par;
    fileName = fName;
    if (fileName.size() == 0)
        createForm("mainform", pwgt);
    else
        createForm(fileName, pwgt);
    return true;
}


void Form::close() {
    disconnect(formWidget, 0, 0, 0);
    if (defaultForm) {
//        delete formWidget;
    }
}


void Form::createForm(QString fileName, QWidget* pwgt) {
    if (parent != 0)
    {
        configName = getParent()->getTagName();
    }
    else
    {
        configName = "Form";
    }
    setObjectName(configName);
    uiCreated = false;
    iconsSeted = false;
    formWidget = 0;
    defaultForm = true;
    script = "";
    fileName = TApplication::exemplar()->getFormsPath(fileName);
    QFile file(fileName + ".ui");
    if (file.open(QIODevice::ReadOnly)) {
        QUiLoader loader;
        loader.addPluginPath("./plugins/");
        formWidget = (Dialog*)loader.load(&file);
        file.close();

        // Удалим пустые объекты в форме, если они имеются после загрузки
/*        for (int i = widget->children().count() - 1; i >= 0; i--)
            if (widget->children().at(i)->objectName().length() == 0 || widget->children().at(i)->metaObject() == 0) {
                QObjectList list = widget->children();
                list.removeAt(i);
            }
*/
        if (QString(formWidget->metaObject()->className()).compare("QDialog") == 0) {
            formWidget->setParent(pwgt);
            formWidget->setVisible(false);
            formWidget->setWindowFlags(Qt::Window | Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowContextHelpButtonHint);
            buttonOk = qFindChild<QPushButton*>(formWidget, "buttonOk");
            buttonCancel = qFindChild<QPushButton*>(formWidget, "buttonCancel");
            cmdButtonLayout = qFindChild<QHBoxLayout*>(formWidget, "cmdButtonLayout");
            vbxLayout = qFindChild<QVBoxLayout*>(formWidget, "vbxLayout");
//            QList<QTableView*> tableViewList = qFindChildren<QTableView*>(formWidget);
//            foreach(QTableView* tv, tableViewList)
//                ((TableView*)tv)->setApp(app);
            defaultForm = false;
        }
    }
    if (formWidget == 0) {
        formWidget = new Dialog(pwgt);
        formWidget->setVisible(false);
        buttonOk = new QPushButton();
        buttonOk->setObjectName("buttonOk");
        buttonCancel = new QPushButton();
        buttonCancel->setObjectName("buttonCancel");

        cmdButtonLayout = new QHBoxLayout();
        cmdButtonLayout->setObjectName("cmdButtonLayout");
        cmdButtonLayout->addStretch(1);
        cmdButtonLayout->addWidget(buttonOk);
        cmdButtonLayout->addWidget(buttonCancel);

        vbxLayout = new QVBoxLayout();
        vbxLayout->setObjectName("vbxLayout");

        vbxLayout->addLayout(cmdButtonLayout);
        formWidget->setLayout(vbxLayout);
    }
    if (buttonOk != 0)
        connect(buttonOk, SIGNAL(clicked()), SLOT(cmdOk()));
    if (buttonCancel != 0)
    {
        connect(buttonCancel, SIGNAL(clicked()), SLOT(cmdCancel()));
        connect(formWidget, SIGNAL(finished(int)), SLOT(cmdCancel()));
    }
    formWidget->setFocusPolicy(Qt::StrongFocus);
}


void Form::setIcons() {
    if (!iconsSeted) {
        QList<QPushButton*> widgets = qFindChildren<QPushButton*>(formWidget);
        for (int i = 0; i < widgets.size(); i++)
            widgets.at(i)->setIcon(QIcon(":" + widgets.at(i)->objectName()));
        iconsSeted = true;
    }
}


void Form::cmdOk() {
    hide();
    lSelected = true;
    if (parent != 0)
        parent->cmdOk();
}


void Form::cmdCancel() {
    lSelected = false;
    hide();
}


int Form::exec() {
    if (formWidget != 0) {
        lSelected = false;
        if (parent != 0)
            beforeShowFormEvent();
        formWidget->exec();
        return lSelected;
    }
    return 0;
}


void Form::show() {
    if (formWidget != 0) {
        lSelected = false;
        if (parent != 0)
            beforeShowFormEvent();
        formWidget->activateWindow();
        formWidget->show();
    }
}


void Form::hide() {
    if (formWidget != 0) {
        formWidget->hide();
        if (parent != 0)
            afterHideFormEvent();
    }
}


void Form::initFormEvent() {
    if (getParent()->getScriptEngine() != 0) {
        getParent()->getScriptEngine()->eventInitForm(this);
    }
}


void Form::beforeShowFormEvent() {
    if (getParent()->getScriptEngine() != 0) {
        getParent()->getScriptEngine()->eventBeforeShowForm(this);
    }
}


void Form::afterHideFormEvent() {
    if (getParent()->getScriptEngine() != 0)
        getParent()->getScriptEngine()->eventAfterHideForm(this);
}


void Form::closeFormEvent() {
    if (getParent()->getScriptEngine() != 0) {
        getParent()->getScriptEngine()->eventCloseForm(this);
    }
}


void Form::setButtonsSignals()
{
    QList<QPushButton*> allButtons = formWidget->findChildren<QPushButton*>();
    foreach (QPushButton* button, allButtons)
    {
        connect(button, SIGNAL(clicked()), SLOT(buttonPressedSignalSend()));
    }
}


/*
void Form::keyPressEvent(QKeyEvent* event) {
    if ((event->modifiers() == Qt::ControlModifier)                                     // Были нажаты клавиши <Ctrl>
            && ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return))) {   // и <Enter>
        cmdOk();
    }
    else {
        if (event->key() == Qt::Key_Escape)
            cmdCancel();
        else
            formWidget->keyPressEvent(event);
    }
}
*/

/*
void Form::closeEvent(QCloseEvent* event) {
    cmdCancel();
    formWidget->closeEvent(event);
}
*/

void Form::readSettings() {
    QSettings settings;
    if (settings.status() == QSettings::NoError) {
          settings.beginGroup(configName);
          formWidget->setGeometry(settings.value("x", 100).toInt(), settings.value("y", 100).toInt(), settings.value("width", 400).toInt(), settings.value("height", 400).toInt());
          settings.endGroup();
    }
}


void Form::writeSettings() {
    QSettings settings;
    settings.beginGroup(configName);
    settings.setValue("x", formWidget->geometry().x());
    settings.setValue("y", formWidget->geometry().y());
    settings.setValue("width", formWidget->geometry().width());
    settings.setValue("height", formWidget->geometry().height());
    settings.endGroup();
}


QDomElement Form::createBoxLayoutElement(QLayout* obj) {
    QDomDocument* doc = new QDomDocument();
    QDomElement element;
    element = doc->createElement("widget");
    element.setAttribute("class", "QWidget");
    if (obj->objectName().size() > 0)
        element.setAttribute("name", obj->objectName());
    QDomElement geometry = doc->createElement("property");
    geometry.setAttribute("name", "geometry");
    QDomElement rect = doc->createElement("rect");
    QDomElement x = doc->createElement("x");
    x.appendChild(doc->createTextNode(QString("%1").arg(obj->geometry().x())));
    rect.appendChild(x);
    QDomElement y = doc->createElement("y");
    y.appendChild(doc->createTextNode(QString("%1").arg(obj->geometry().y())));
    rect.appendChild(y);
    QDomElement width = doc->createElement("width");
    width.appendChild(doc->createTextNode(QString("%1").arg(obj->geometry().width())));
    rect.appendChild(width);
    QDomElement height = doc->createElement("height");
    height.appendChild(doc->createTextNode(QString("%1").arg(obj->geometry().height())));
    rect.appendChild(height);
    geometry.appendChild(rect);
    element.appendChild(geometry);
    delete doc;
    return element;
}


QDomElement Form::createPushButtonElement(QWidget* obj) {
//#ifdef Q_OS_WIN32
//    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
//#else
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
//#endif
    QDomDocument* doc = new QDomDocument();
    QDomElement element;
    element = doc->createElement("widget");
    element.setAttribute("class", "QPushButton");
    if (obj->objectName().size() > 0)
        element.setAttribute("name", obj->objectName());
    QDomElement geometry = doc->createElement("property");
    geometry.setAttribute("name", "geometry");
    QDomElement rect = doc->createElement("rect");
    QDomElement x = doc->createElement("x");
    x.appendChild(doc->createTextNode(QString("%1").arg(obj->x())));
    rect.appendChild(x);
    QDomElement y = doc->createElement("y");
    y.appendChild(doc->createTextNode(QString("%1").arg(obj->y())));
    rect.appendChild(y);
    QDomElement width = doc->createElement("width");
    width.appendChild(doc->createTextNode(QString("%1").arg(obj->width())));
    rect.appendChild(width);
    QDomElement height = doc->createElement("height");
    height.appendChild(doc->createTextNode(QString("%1").arg(obj->height())));
    rect.appendChild(height);
    geometry.appendChild(rect);
    element.appendChild(geometry);
    QDomElement text = doc->createElement("property");
    text.setAttribute("name", "text");
    QDomElement textString = doc->createElement("string");
    textString.appendChild(doc->createTextNode(QString(codec->toUnicode(((QPushButton*)obj)->text().toUtf8()))));
    text.appendChild(textString);
    element.appendChild(text);
    QDomElement icon = doc->createElement("property");
    icon.setAttribute("name", "icon");
    QDomElement str1, str2;
    str1 = doc->createElement("iconset");
    str1.setAttribute("resource", TApplication::resourcesFile());
    str2 = doc->createElement("normalon");
    str2.appendChild(doc->createTextNode(":" + ((QPushButton*)obj)->objectName()));
    str1.appendChild(str2);
    str2 = doc->createElement("normaloff");
    str2.appendChild(doc->createTextNode(":" + ((QPushButton*)obj)->objectName()));
    str1.appendChild(str2);
    str2 = doc->createElement("activeon");
    str2.appendChild(doc->createTextNode(":" + ((QPushButton*)obj)->objectName()));
    str1.appendChild(str2);
    str2 = doc->createElement("activeoff");
    str2.appendChild(doc->createTextNode(":" + ((QPushButton*)obj)->objectName()));
    str1.appendChild(str2);
    str2 = doc->createElement("selectedon");
    str2.appendChild(doc->createTextNode(":" + ((QPushButton*)obj)->objectName()));
    str1.appendChild(str2);
    str2 = doc->createElement("selectedoff");
    str2.appendChild(doc->createTextNode(":" + ((QPushButton*)obj)->objectName()));
    str1.appendChild(str2);
    icon.appendChild(str1);
    element.appendChild(icon);
    delete doc;
    return element;
}


QDomElement Form::createLabelElement(QString label) {
//#ifdef Q_OS_WIN32
//    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
//#else
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
//#endif
    QDomDocument* doc = new QDomDocument();
    QDomElement item, widget;
    widget = doc->createElement("widget");
    widget.setAttribute("class", "QLabel");
    widget.setAttribute("name", "label");
    item = doc->createElement("property");
    item.setAttribute("name", "sizePolicy");
    QDomElement sizePolicy = doc->createElement("sizePolicy");
    sizePolicy.setAttribute("hsizetype", "Fixed");
    sizePolicy.setAttribute("vsizetype", "Fixed");
    item.appendChild(sizePolicy);
    widget.appendChild(item);
    item = doc->createElement("property");
    item.setAttribute("name", "text");
    QDomElement textString = doc->createElement("string");
    textString.appendChild(doc->createTextNode(QString(codec->toUnicode(label.toUtf8()))));
    item.appendChild(textString);
    widget.appendChild(item);
    delete doc;
    return widget;
}


QDomElement Form::createLineEditElement(QLineEdit* obj) {
    QDomDocument* doc = new QDomDocument();
    QDomElement item, element, widget;
    widget = doc->createElement("widget");
    widget.setAttribute("class", obj->metaObject()->className());
    widget.setAttribute("name", obj->objectName());
    item = doc->createElement("property");
    item.setAttribute("name", "sizePolicy");
    QDomElement sizePolicy = doc->createElement("sizePolicy");
    sizePolicy.setAttribute("hsizetype", "Fixed");
    sizePolicy.setAttribute("vsizetype", "Fixed");
    item.appendChild(sizePolicy);
    widget.appendChild(item);
    item = doc->createElement("property");
    item.setAttribute("name", "font");
    QDomElement font = doc->createElement("font");
    element = doc->createElement("pointsize");
    element.appendChild(doc->createTextNode(QString("%1").arg(obj->font().pointSize())));
    font.appendChild(element);
    element = doc->createElement("bold");
    element.appendChild(doc->createTextNode(QString(obj->font().bold() ? "true" : "false")));
    font.appendChild(element);
    item.appendChild(font);
    widget.appendChild(item);
    item = doc->createElement("property");
    item.setAttribute("name", "readOnly");
    element = doc->createElement("bool");
    element.appendChild(doc->createTextNode(QString(obj->isReadOnly() ? "true" : "false")));
    item.appendChild(element);
    widget.appendChild(item);
    delete doc;
    return widget;
}


QDomElement Form::createDateEditElement(QDateEdit* obj) {
    QDomDocument* doc = new QDomDocument();
    QDomElement item, element, widget;
    widget = doc->createElement("widget");
    widget.setAttribute("class", obj->metaObject()->className());
    widget.setAttribute("name", obj->objectName());
    item = doc->createElement("property");
    item.setAttribute("name", "sizePolicy");
    QDomElement sizePolicy = doc->createElement("sizePolicy");
    sizePolicy.setAttribute("hsizetype", "Fixed");
    sizePolicy.setAttribute("vsizetype", "Fixed");
    item.appendChild(sizePolicy);
    widget.appendChild(item);
    item = doc->createElement("property");
    item.setAttribute("name", "font");
    QDomElement font = doc->createElement("font");
    element = doc->createElement("pointsize");
    element.appendChild(doc->createTextNode(QString("%1").arg(obj->font().pointSize())));
    font.appendChild(element);
    element = doc->createElement("bold");
    element.appendChild(doc->createTextNode(QString(obj->font().bold() ? "true" : "false")));
    font.appendChild(element);
    item.appendChild(font);
    widget.appendChild(item);
    item = doc->createElement("property");
    item.setAttribute("name", "readOnly");
    element = doc->createElement("bool");
    element.appendChild(doc->createTextNode(QString(obj->isReadOnly() ? "true" : "false")));
    item.appendChild(element);
    widget.appendChild(item);
    delete doc;
    return widget;
}


QDomElement Form::createHStretchElement() {
    QDomDocument* doc = new QDomDocument();
    QDomElement element, str1;
    element = doc->createElement("spacer");
    element.setAttribute("name", "horizontalSpacer");
    QDomElement orientation = doc->createElement("property");
    orientation.setAttribute("name", "orientation");
    str1 = doc->createElement("enum");
    str1.appendChild(doc->createTextNode("Qt::Horizontal"));
    orientation.appendChild(str1);
    element.appendChild(orientation);
    QDomElement sizeHint = doc->createElement("property");
    sizeHint.setAttribute("name", "sizeHint");
    sizeHint.setAttribute("stdset", "0");
    QDomElement size = doc->createElement("size");
    QDomElement width = doc->createElement("width");
    width.appendChild(doc->createTextNode(QString("%1").arg(40)));
    size.appendChild(width);
    QDomElement height = doc->createElement("height");
    height.appendChild(doc->createTextNode(QString("%1").arg(20)));
    size.appendChild(height);
    sizeHint.appendChild(size);
    element.appendChild(sizeHint);
    delete doc;
    return element;
}


QDomElement Form::createVStretchElement() {
    QDomDocument* doc = new QDomDocument();
    QDomElement element, str1;
    element = doc->createElement("spacer");
    element.setAttribute("name", "vertucalSpacer");
    QDomElement orientation = doc->createElement("property");
    orientation.setAttribute("name", "orientation");
    str1 = doc->createElement("enum");
    str1.appendChild(doc->createTextNode("Qt::Vertical"));
    orientation.appendChild(str1);
    element.appendChild(orientation);
    QDomElement sizeHint = doc->createElement("property");
    sizeHint.setAttribute("name", "sizeHint");
    sizeHint.setAttribute("stdset", "0");
    QDomElement size = doc->createElement("size");
    QDomElement width = doc->createElement("width");
    width.appendChild(doc->createTextNode(QString("%1").arg(40)));
    size.appendChild(width);
    QDomElement height = doc->createElement("height");
    height.appendChild(doc->createTextNode(QString("%1").arg(20)));
    size.appendChild(height);
    sizeHint.appendChild(size);
    element.appendChild(sizeHint);
    delete doc;
    return element;
}


QDomElement Form::createWidgetsStructure() {
    QDomDocument* doc = new QDomDocument();
    QDomElement item;

    // создадим горизонтальный лейаут с кнопками
    QDomElement hboxLayout,
                hlayout;
    if (cmdButtonLayout != 0) {
        hlayout = doc->createElement("layout");
        hlayout.setAttribute("class", "QHBoxLayout");
        hlayout.setAttribute("name", cmdButtonLayout->objectName());
        item = doc->createElement("item");
        item.appendChild(createHStretchElement());
        hlayout.appendChild(item);
        if (buttonOk != 0) {
            item = doc->createElement("item");
            item.appendChild(createPushButtonElement((QWidget*)buttonOk));
            hlayout.appendChild(item);
        }
        if (buttonCancel != 0) {
            item = doc->createElement("item");
            item.appendChild(createPushButtonElement((QWidget*)buttonCancel));
            hlayout.appendChild(item);
        }
        hboxLayout = createBoxLayoutElement(cmdButtonLayout);
        hboxLayout.appendChild(hlayout);
    }

    QDomElement vlayout;
    if (vbxLayout != 0) {
       vlayout = doc->createElement("layout");
       vlayout.setAttribute("class", "QVBoxLayout");
       vlayout.setAttribute("name", vbxLayout->objectName());
       item = doc->createElement("item");
       item.appendChild(hboxLayout);
       vlayout.appendChild(item);
    }
    delete doc;
    return vlayout;
}


void Form::createUi() {
//#ifdef Q_OS_WIN32
//    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
//#else
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
//#endif
    if (getConfigName().size() > 0) {
        QString fileName = "./defaultforms/" + getParent()->getTagName() + ".ui";
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream text(&file);
            QDomDocument* doc = new QDomDocument();
            QDomElement root, cl;
            root = doc->createElement("UI");
            root.setAttribute("version", "4.0");
            root.setAttribute("stdsetdef", "1");
            cl = doc->createElement("class");
            cl.appendChild(doc->createTextNode("Dialog"));
            root.appendChild(cl);
            cl = doc->createElement("widget");
            cl.setAttribute("class", "Dialog");
            cl.setAttribute("name", formWidget->objectName());
            QDomElement nameString = doc->createElement("string");
            nameString.appendChild(doc->createTextNode(QString(codec->toUnicode(configName.toUtf8()))));
            QDomElement name = doc->createElement("property");
            name.setAttribute("name", "name");
            name.appendChild(nameString);
            cl.appendChild(name);
            QDomElement geometry = doc->createElement("property");
            geometry.setAttribute("name", "geometry");
            QDomElement rect = doc->createElement("rect");
            QDomElement xForm = doc->createElement("x");
            xForm.appendChild(doc->createTextNode(QString("%1").arg(formWidget->x())));
            rect.appendChild(xForm);
            QDomElement yForm = doc->createElement("y");
            yForm.appendChild(doc->createTextNode(QString("%1").arg(formWidget->y())));
            rect.appendChild(yForm);
            QDomElement widthForm = doc->createElement("width");
            widthForm.appendChild(doc->createTextNode(QString("%1").arg(formWidget->width())));
            rect.appendChild(widthForm);
            QDomElement heightForm = doc->createElement("height");
            heightForm.appendChild(doc->createTextNode(QString("%1").arg(formWidget->height())));
            rect.appendChild(heightForm);
            geometry.appendChild(rect);
            cl.appendChild(geometry);
            QDomElement caption = doc->createElement("property");
            caption.setAttribute("name", "caption");
            QDomElement captionString = doc->createElement("string");
            captionString.appendChild(doc->createTextNode(QString(codec->toUnicode(formWidget->windowTitle().toUtf8()))));
            caption.appendChild(captionString);
            cl.appendChild(caption);
            cl.appendChild(createWidgetsStructure());
            root.appendChild(cl);
            QDomElement resources = doc->createElement("resources");
            QDomElement include = doc->createElement("include");
            include.setAttribute("location", TApplication::resourcesFile());
            resources.appendChild(include);
            root.appendChild(resources);
            doc->appendChild(root);
            text << "<?xml " + doc->createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"").data() + "?>" << endl;
            text << doc->toString();
//            doc->save(text, 4);
            file.close();
            uiCreated = true;
            delete doc;
        }
    }
}
