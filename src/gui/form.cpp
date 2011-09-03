#include <QObject>
#include <QTextStream>
#include <QFormBuilder>
#include <QResource>
#include <QUiLoader>
#include <QTextCodec>
#include "form.h"
#include "../app.h"
#include "../essence.h"
#include "mainwindow.h"


class App;
extern App* app;
extern QString programResourcesFile;

bool Form::open(QWidget* pwgt, Essence* par) {
    parent = par;
    if (parent != 0) {
        createForm(parent->getConfigName() + "/mainform", pwgt);
    }
    else
        createForm("", pwgt);
    return true;
}

bool Form::open(QString fileName, QObject* form) {
    parent = 0;
    if (form != 0)
        createForm(((Form*)form)->getParent()->getConfigName() + "/" + fileName, ((Form*)form)->getForm());
    else
        createForm(fileName);
    return true;
}

void Form::close() {
    disconnect(formWidget, 0, 0, 0);
    if (defaultForm) {
        delete formWidget;
    }
}

void Form::createForm(QString fileName, QWidget* pwgt) {
    configName = "Form";
    setObjectName(configName);
    uiCreated = false;
    iconsSeted = false;
    formWidget = 0;
    defaultForm = true;
    script = "";
    engine = 0;                                 // По умолчанию не создается никакой скриптовый движок
    fileName = app->getFormsPath(fileName);
    QFile file(fileName + ".ui");
    if (file.open(QIODevice::ReadOnly)) {
        QUiLoader loader;
        loader.addPluginPath("./plugins/");
        formWidget = (QDialog*)loader.load(&file);
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
        formWidget = new QDialog(pwgt);
        formWidget->setVisible(false);
        buttonOk = new QPushButton(tr("&Принять"));
        buttonOk->setObjectName("buttonOk");
        buttonCancel = new QPushButton(tr("&Отменить"));
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
        connect(buttonOk, SIGNAL(clicked()), this, SLOT(cmdOk()));
    if (buttonCancel != 0) {
        connect(buttonCancel, SIGNAL(clicked()), this, SLOT(cmdCancel()));
        connect(formWidget, SIGNAL(finished(int)), this, SLOT(cmdCancel()));
    }
    formWidget->setFocusPolicy(Qt::StrongFocus);
    setScriptForForm(fileName + ".js");
}

void Form::setIcons() {
    if (!iconsSeted) {
//        QList<QPushButton*> widgets = formWidget->findChildren<QPushButton*>();
        QList<QPushButton*> widgets = qFindChildren<QPushButton*>(formWidget);
        for (int i = 0; i < widgets.size(); i++)
            widgets.at(i)->setIcon(QIcon(":" + widgets.at(i)->objectName()));
        iconsSeted = true;
    }
}

void Form::cmdOk() {
    lSelected = true;
    if (parent != 0)
        parent->cmdOk();
    hide();
}

void Form::cmdCancel() {
    lSelected = false;
    hide();
}

int Form::doExec() {
    if (formWidget != 0) {
        lSelected = false;
        setIcons();
        beforeShowFormEvent();
        formWidget->exec();
        return lSelected;
    }
    return 0;
}

void Form::doShow() {
    if (formWidget != 0) {
        lSelected = false;
        setIcons();
        beforeShowFormEvent();
        formWidget->show();
//        if (!uiCreated && defaultForm)
//            createUi();
    }
}

void Form::doHide() {
    if (formWidget != 0) {
        formWidget->hide();
        afterHideFormEvent();
    }
}

void Form::initFormEvent() {
    if (engine != 0) {
        engine->globalObject().property("initForm").call();
    }
}

void Form::beforeShowFormEvent() {
    if (engine != 0) {
        engine->globalObject().property("beforeShowForm").call();
    }
}

void Form::afterHideFormEvent() {
    if (engine != 0)
        engine->globalObject().property("afterHideForm").call();
}

void Form::closeFormEvent() {
    if (engine != 0) {
        engine->globalObject().property("closeForm").call();
    }
}

void Form::setScriptForForm(QString scr) {
    QFile file(scr);
    if (file.open(QFile::ReadOnly)) {
       if (engine == 0) {
          engine = new ScriptEngine(this);
//          engine->setParentForm();
       }
       engine->globalObject().setProperty("MainForm", engine->newQObject(formWidget));
       script = file.readAll();
       scripts = engine->evaluate(script);
    }
}

void Form::removeScriptForForm() {
    if (engine != 0)
        delete engine;
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
    QDomDocument doc;
    QDomElement element;
    element = doc.createElement("widget");
    element.setAttribute("class", "QWidget");
    if (obj->objectName().size() > 0)
        element.setAttribute("name", obj->objectName());
    QDomElement geometry = doc.createElement("property");
    geometry.setAttribute("name", "geometry");
    QDomElement rect = doc.createElement("rect");
    QDomElement x = doc.createElement("x");
    x.appendChild(doc.createTextNode(QString("%1").arg(obj->geometry().x())));
    rect.appendChild(x);
    QDomElement y = doc.createElement("y");
    y.appendChild(doc.createTextNode(QString("%1").arg(obj->geometry().y())));
    rect.appendChild(y);
    QDomElement width = doc.createElement("width");
    width.appendChild(doc.createTextNode(QString("%1").arg(obj->geometry().width())));
    rect.appendChild(width);
    QDomElement height = doc.createElement("height");
    height.appendChild(doc.createTextNode(QString("%1").arg(obj->geometry().height())));
    rect.appendChild(height);
    geometry.appendChild(rect);
    element.appendChild(geometry);
    return element;
}

QDomElement Form::createPushButtonElement(QWidget* obj) {
#ifdef Q_OS_WIN32
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
#else
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
#endif
    QDomDocument doc;
    QDomElement element;
    element = doc.createElement("widget");
    element.setAttribute("class", "QPushButton");
    if (obj->objectName().size() > 0)
        element.setAttribute("name", obj->objectName());
    QDomElement geometry = doc.createElement("property");
    geometry.setAttribute("name", "geometry");
    QDomElement rect = doc.createElement("rect");
    QDomElement x = doc.createElement("x");
    x.appendChild(doc.createTextNode(QString("%1").arg(obj->x())));
    rect.appendChild(x);
    QDomElement y = doc.createElement("y");
    y.appendChild(doc.createTextNode(QString("%1").arg(obj->y())));
    rect.appendChild(y);
    QDomElement width = doc.createElement("width");
    width.appendChild(doc.createTextNode(QString("%1").arg(obj->width())));
    rect.appendChild(width);
    QDomElement height = doc.createElement("height");
    height.appendChild(doc.createTextNode(QString("%1").arg(obj->height())));
    rect.appendChild(height);
    geometry.appendChild(rect);
    element.appendChild(geometry);
    QDomElement text = doc.createElement("property");
    text.setAttribute("name", "text");
    QDomElement textString = doc.createElement("string");
    textString.appendChild(doc.createTextNode(QString(codec->toUnicode(((QPushButton*)obj)->text().toUtf8()))));
    text.appendChild(textString);
    element.appendChild(text);
    QDomElement icon = doc.createElement("property");
    icon.setAttribute("name", "icon");
    QDomElement str1, str2;
    str1 = doc.createElement("iconset");
    str1.setAttribute("resource", programResourcesFile);
    str2 = doc.createElement("normalon");
    str2.appendChild(doc.createTextNode(":" + ((QPushButton*)obj)->objectName()));
    str1.appendChild(str2);
    str2 = doc.createElement("normaloff");
    str2.appendChild(doc.createTextNode(":" + ((QPushButton*)obj)->objectName()));
    str1.appendChild(str2);
    str2 = doc.createElement("activeon");
    str2.appendChild(doc.createTextNode(":" + ((QPushButton*)obj)->objectName()));
    str1.appendChild(str2);
    str2 = doc.createElement("activeoff");
    str2.appendChild(doc.createTextNode(":" + ((QPushButton*)obj)->objectName()));
    str1.appendChild(str2);
    str2 = doc.createElement("selectedon");
    str2.appendChild(doc.createTextNode(":" + ((QPushButton*)obj)->objectName()));
    str1.appendChild(str2);
    str2 = doc.createElement("selectedoff");
    str2.appendChild(doc.createTextNode(":" + ((QPushButton*)obj)->objectName()));
    str1.appendChild(str2);
    icon.appendChild(str1);
    element.appendChild(icon);
    return element;
}

QDomElement Form::createLabelElement(QString label) {
#ifdef Q_OS_WIN32
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
#else
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
#endif
    QDomDocument doc;
    QDomElement item, widget;
    widget = doc.createElement("widget");
    widget.setAttribute("class", "QLabel");
    widget.setAttribute("name", "label");
    item = doc.createElement("property");
    item.setAttribute("name", "sizePolicy");
    QDomElement sizePolicy = doc.createElement("sizePolicy");
    sizePolicy.setAttribute("hsizetype", "Fixed");
    sizePolicy.setAttribute("vsizetype", "Fixed");
    item.appendChild(sizePolicy);
    widget.appendChild(item);
    item = doc.createElement("property");
    item.setAttribute("name", "text");
    QDomElement textString = doc.createElement("string");
    textString.appendChild(doc.createTextNode(QString(codec->toUnicode(label.toUtf8()))));
    item.appendChild(textString);
    widget.appendChild(item);
    return widget;
}

QDomElement Form::createLineEditElement(QLineEdit* obj) {
    QDomDocument doc;
    QDomElement item, element, widget;
    widget = doc.createElement("widget");
    widget.setAttribute("class", obj->metaObject()->className());
    widget.setAttribute("name", obj->objectName());
    item = doc.createElement("property");
    item.setAttribute("name", "sizePolicy");
    QDomElement sizePolicy = doc.createElement("sizePolicy");
    sizePolicy.setAttribute("hsizetype", "Fixed");
    sizePolicy.setAttribute("vsizetype", "Fixed");
    item.appendChild(sizePolicy);
    widget.appendChild(item);
    item = doc.createElement("property");
    item.setAttribute("name", "font");
    QDomElement font = doc.createElement("font");
    element = doc.createElement("pointsize");
    element.appendChild(doc.createTextNode(QString("%1").arg(obj->font().pointSize())));
    font.appendChild(element);
    element = doc.createElement("bold");
    element.appendChild(doc.createTextNode(QString(obj->font().bold() ? "true" : "false")));
    font.appendChild(element);
    item.appendChild(font);
    widget.appendChild(item);
    item = doc.createElement("property");
    item.setAttribute("name", "readOnly");
    element = doc.createElement("bool");
    element.appendChild(doc.createTextNode(QString(obj->isReadOnly() ? "true" : "false")));
    item.appendChild(element);
    widget.appendChild(item);
    return widget;
}

QDomElement Form::createDateEditElement(QDateEdit* obj) {
    QDomDocument doc;
    QDomElement item, element, widget;
    widget = doc.createElement("widget");
    widget.setAttribute("class", obj->metaObject()->className());
    widget.setAttribute("name", obj->objectName());
    item = doc.createElement("property");
    item.setAttribute("name", "sizePolicy");
    QDomElement sizePolicy = doc.createElement("sizePolicy");
    sizePolicy.setAttribute("hsizetype", "Fixed");
    sizePolicy.setAttribute("vsizetype", "Fixed");
    item.appendChild(sizePolicy);
    widget.appendChild(item);
    item = doc.createElement("property");
    item.setAttribute("name", "font");
    QDomElement font = doc.createElement("font");
    element = doc.createElement("pointsize");
    element.appendChild(doc.createTextNode(QString("%1").arg(obj->font().pointSize())));
    font.appendChild(element);
    element = doc.createElement("bold");
    element.appendChild(doc.createTextNode(QString(obj->font().bold() ? "true" : "false")));
    font.appendChild(element);
    item.appendChild(font);
    widget.appendChild(item);
    item = doc.createElement("property");
    item.setAttribute("name", "readOnly");
    element = doc.createElement("bool");
    element.appendChild(doc.createTextNode(QString(obj->isReadOnly() ? "true" : "false")));
    item.appendChild(element);
    widget.appendChild(item);
    return widget;
}

QDomElement Form::createHStretchElement() {
    QDomDocument doc;
    QDomElement element, str1;
    element = doc.createElement("spacer");
    element.setAttribute("name", "horizontalSpacer");
    QDomElement orientation = doc.createElement("property");
    orientation.setAttribute("name", "orientation");
    str1 = doc.createElement("enum");
    str1.appendChild(doc.createTextNode("Qt::Horizontal"));
    orientation.appendChild(str1);
    element.appendChild(orientation);
    QDomElement sizeHint = doc.createElement("property");
    sizeHint.setAttribute("name", "sizeHint");
    sizeHint.setAttribute("stdset", "0");
    QDomElement size = doc.createElement("size");
    QDomElement width = doc.createElement("width");
    width.appendChild(doc.createTextNode(QString("%1").arg(40)));
    size.appendChild(width);
    QDomElement height = doc.createElement("height");
    height.appendChild(doc.createTextNode(QString("%1").arg(20)));
    size.appendChild(height);
    sizeHint.appendChild(size);
    element.appendChild(sizeHint);
    return element;
}

QDomElement Form::createVStretchElement() {
    QDomDocument doc;
    QDomElement element, str1;
    element = doc.createElement("spacer");
    element.setAttribute("name", "vertucalSpacer");
    QDomElement orientation = doc.createElement("property");
    orientation.setAttribute("name", "orientation");
    str1 = doc.createElement("enum");
    str1.appendChild(doc.createTextNode("Qt::Vertical"));
    orientation.appendChild(str1);
    element.appendChild(orientation);
    QDomElement sizeHint = doc.createElement("property");
    sizeHint.setAttribute("name", "sizeHint");
    sizeHint.setAttribute("stdset", "0");
    QDomElement size = doc.createElement("size");
    QDomElement width = doc.createElement("width");
    width.appendChild(doc.createTextNode(QString("%1").arg(40)));
    size.appendChild(width);
    QDomElement height = doc.createElement("height");
    height.appendChild(doc.createTextNode(QString("%1").arg(20)));
    size.appendChild(height);
    sizeHint.appendChild(size);
    element.appendChild(sizeHint);
    return element;
}

QDomElement Form::createWidgetsStructure() {
    QDomDocument doc;
    QDomElement item;

    // создадим горизонтальный лейаут с кнопками
    QDomElement hboxLayout,
                hlayout;
    if (cmdButtonLayout != 0) {
        hlayout = doc.createElement("layout");
        hlayout.setAttribute("class", "QHBoxLayout");
        hlayout.setAttribute("name", cmdButtonLayout->objectName());
        item = doc.createElement("item");
        item.appendChild(createHStretchElement());
        hlayout.appendChild(item);
        if (buttonOk != 0) {
            item = doc.createElement("item");
            item.appendChild(createPushButtonElement((QWidget*)buttonOk));
            hlayout.appendChild(item);
        }
        if (buttonCancel != 0) {
            item = doc.createElement("item");
            item.appendChild(createPushButtonElement((QWidget*)buttonCancel));
            hlayout.appendChild(item);
        }
        hboxLayout = createBoxLayoutElement(cmdButtonLayout);
        hboxLayout.appendChild(hlayout);
    }

    QDomElement vlayout;
    if (vbxLayout != 0) {
       vlayout = doc.createElement("layout");
       vlayout.setAttribute("class", "QVBoxLayout");
       vlayout.setAttribute("name", vbxLayout->objectName());
       item = doc.createElement("item");
       item.appendChild(hboxLayout);
       vlayout.appendChild(item);
    }
    return vlayout;
}

void Form::createUi() {
#ifdef Q_OS_WIN32
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
#else
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
#endif
    if (getParent()->getConfigName().size() > 0) {
        QString fileName = "./defaultforms/" + getParent()->getConfigName() + ".ui";
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream text(&file);
            QDomDocument doc;
            QDomElement root, cl;
            root = doc.createElement("UI");
            root.setAttribute("version", "4.0");
            root.setAttribute("stdsetdef", "1");
            cl = doc.createElement("class");
            cl.appendChild(doc.createTextNode("Dialog"));
            root.appendChild(cl);
            cl = doc.createElement("widget");
            cl.setAttribute("class", "QDialog");
            cl.setAttribute("name", formWidget->objectName());
            QDomElement nameString = doc.createElement("string");
            nameString.appendChild(doc.createTextNode(QString(codec->toUnicode(configName.toUtf8()))));
            QDomElement name = doc.createElement("property");
            name.setAttribute("name", "name");
            name.appendChild(nameString);
            cl.appendChild(name);
            QDomElement geometry = doc.createElement("property");
            geometry.setAttribute("name", "geometry");
            QDomElement rect = doc.createElement("rect");
            QDomElement xForm = doc.createElement("x");
            xForm.appendChild(doc.createTextNode(QString("%1").arg(formWidget->x())));
            rect.appendChild(xForm);
            QDomElement yForm = doc.createElement("y");
            yForm.appendChild(doc.createTextNode(QString("%1").arg(formWidget->y())));
            rect.appendChild(yForm);
            QDomElement widthForm = doc.createElement("width");
            widthForm.appendChild(doc.createTextNode(QString("%1").arg(formWidget->width())));
            rect.appendChild(widthForm);
            QDomElement heightForm = doc.createElement("height");
            heightForm.appendChild(doc.createTextNode(QString("%1").arg(formWidget->height())));
            rect.appendChild(heightForm);
            geometry.appendChild(rect);
            cl.appendChild(geometry);
            QDomElement caption = doc.createElement("property");
            caption.setAttribute("name", "caption");
            QDomElement captionString = doc.createElement("string");
            captionString.appendChild(doc.createTextNode(QString(codec->toUnicode(formWidget->windowTitle().toUtf8()))));
            caption.appendChild(captionString);
            cl.appendChild(caption);
            cl.appendChild(createWidgetsStructure());
            root.appendChild(cl);
            QDomElement resources = doc.createElement("resources");
            QDomElement include = doc.createElement("include");
            include.setAttribute("location", programResourcesFile);
            resources.appendChild(include);
            root.appendChild(resources);
            doc.appendChild(root);
            text << "<?xml " + doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"").data() + "?>" << endl;
            text << doc.toString();
//            doc.save(text, 4);
            file.close();
            uiCreated = true;
        }
    }
}
