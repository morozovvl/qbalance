# -------------------------------------------------
# Project created by QtCreator 2009-04-25T16:32:03
# -------------------------------------------------

QT += sql \
      xml \
      core \
      script \
      gui

CONFIG(debug) {
    DESTDIR = bin/debug
}

TARGET = enterprise
CONFIG += designer \
    plugin \
    uitools
CONFIG -= app_bundle
TEMPLATE = app

SOURCES += src/main.cpp \
    src/kernel/app.cpp \
    src/storage/dbfactory.cpp \
    src/gui/passwordform.cpp \
    src/gui/form.cpp \
    src/gui/guifactory.cpp \
    src/gui/connectionform.cpp \
    src/gui/mainwindow.cpp \
    src/gui/calendarform.cpp \
    src/kernel/essence.cpp \
    src/gui/searchparameters.cpp \
    src/gui/formgrid.cpp \
    src/gui/formgridsearch.cpp \
    src/kernel/dictionary.cpp \
    src/kernel/dictionaries.cpp \
    src/gui/mycombobox.cpp \
    src/report/reportengine.cpp \
    src/engine/reportcontextfunctions.cpp \
    src/gui/formdocument.cpp \
    src/kernel/documents.cpp \
    src/storage/mysqlrelationaltablemodel.cpp \
    src/kernel/topers.cpp \
    src/kernel/document.cpp \
    src/storage/table.cpp \
    src/storage/documenttablemodel.cpp \
    src/gui/tableview.cpp \
    src/gui/mynumericitemdelegate.cpp \
    src/gui/mybooleanitemdelegate.cpp \
    src/kernel/saldo.cpp \
    src/gui/docparameters.cpp \
    src/gui/myitemdelegate.cpp \
    src/gui/mylineitemdelegate.cpp \
    src/gui/picture.cpp \
    src/engine/scriptengine.cpp \
    src/gui/mynumericedit.cpp \
    src/report/reports.cpp \
    src/engine/reportscriptengine.cpp \
    src/report/ooreportengine.cpp \
    src/engine/reportcontext.cpp \
    src/engine/formscriptengine.cpp \
    src/storage/mysqlrecord.cpp \
    src/engine/sqlqueryclass.cpp \
    src/engine/sqlqueryprototype.cpp \
    src/engine/sqlrecordclass.cpp \
    src/engine/sqlrecordprototype.cpp \
    src/engine/sqlfieldclass.cpp \
    src/engine/sqlfieldprototype.cpp \
    src/engine/eventloop.cpp \
    src/engine/documentscriptengine.cpp \
    src/gui/configform.cpp \
    src/gui/wizardform.cpp \
    src/gui/mybuttonlineedit.cpp \
    src/gui/mybuttonlineedititemdelegate.cpp \
    src/gui/wizarddictionary.cpp \
    src/gui/wizardoperation.cpp \
    src/gui/mytextedit.cpp \
    src/gui/mysyntaxhighlighter.cpp
HEADERS += src/kernel/app.h \
    src/storage/dbfactory.h \
    src/gui/guifactory.h \
    src/gui/passwordform.h \
    src/gui/form.h \
    src/gui/connectionform.h \
    src/gui/mainwindow.h \
    src/gui/calendarform.h \
    src/kernel/essence.h \
    src/gui/searchparameters.h \
    src/gui/formgrid.h \
    src/gui/formgridsearch.h \
    src/kernel/dictionary.h \
    src/kernel/dictionaries.h \
    src/gui/mycombobox.h \
    src/report/reportengine.h \
    src/gui/formdocument.h \
    src/kernel/documents.h \
    src/storage/mysqlrelationaltablemodel.h \
    src/kernel/topers.h \
    src/kernel/document.h \
    src/storage/table.h \
    src/storage/documenttablemodel.h \
    src/gui/tableview.h \
    src/gui/mynumericitemdelegate.h \
    src/gui/mybooleanitemdelegate.h \
    src/kernel/saldo.h \
    src/gui/docparameters.h \
    src/gui/myitemdelegate.h \
    src/gui/mylineitemdelegate.h \
    src/definitions.h \
    src/gui/picture.h \
    src/engine/scriptengine.h \
    src/gui/mynumericedit.h \
    src/report/reports.h \
    src/engine/reportscriptengine.h \
    src/engine/reportscriptengine.h \
    src/report/ooreportengine.h \
    src/engine/reportcontext.h \
    src/engine/formscriptengine.h \
    src/storage/mysqlrecord.h \
    src/engine/sqlqueryclass.h \
    src/engine/sqlqueryprototype.h \
    src/engine/sqlrecordclass.h \
    src/engine/sqlrecordprototype.h \
    src/engine/sqlfieldclass.h \
    src/engine/sqlfieldprototype.h \
    src/engine/eventloop.h \
    src/engine/documentscriptengine.h \
    src/gui/configform.h \
    src/gui/wizardform.h \
    src/gui/mybuttonlineedit.h \
    src/gui/mybuttonlineedititemdelegate.h \
    src/gui/wizarddictionary.h \
    src/gui/wizardoperation.h \
    src/gui/mytextedit.h \
    src/gui/mysyntaxhighlighter.h
RESOURCES += src/resources.qrc

unix:MOC_DIR = ./.moc
win32:MOC_DIR = /.moc

unix:OBJECTS_DIR = ./.obj
win32:OBJECTS_DIR = /.obj

unix:RCC_DIR = ./src
win32:RCC_DIR = /src
