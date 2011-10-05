# -------------------------------------------------
# Project created by QtCreator 2009-04-25T16:32:03
# -------------------------------------------------

QT += sql
QT += xml
QT += core
QT += script
QT += gui
TARGET = enterprise
CONFIG += designer \
    plugin
CONFIG += uitools
CONFIG -= app_bundle
TEMPLATE = app
#SUBDIRS = src/storage \
#    src/engine \
#    src/kernel
SOURCES += src/main.cpp \
    src/app.cpp \
    src/dbfactory.cpp \
    src/gui/passwordform.cpp \
    src/gui/form.cpp \
    src/gui/guifactory.cpp \
    src/gui/connectionform.cpp \
    src/gui/mainwindow.cpp \
    src/gui/calendarform.cpp \
    src/essence.cpp \
    src/gui/searchparameters.cpp \
    src/gui/formgrid.cpp \
    src/gui/formgridsearch.cpp \
    src/dictionary.cpp \
    src/dictionaries.cpp \
    src/gui/mycombobox.cpp \
    src/reporttemplate.cpp \
    src/reportengine.cpp \
    src/reportcontextfunctions.cpp \
    src/gui/formdocument.cpp \
    src/documents.cpp \
    src/mysqlrelationaltablemodel.cpp \
    src/topers.cpp \
    src/document.cpp \
    src/table.cpp \
    src/documenttablemodel.cpp \
    src/gui/tableview.cpp \
    src/gui/mynumericitemdelegate.cpp \
    src/gui/mybooleanitemdelegate.cpp \
    src/saldo.cpp \
    src/gui/docparameters.cpp \
    src/gui/numericedit.cpp \
    src/gui/myitemdelegate.cpp \
    src/gui/mylineitemdelegate.cpp \
    src/gui/picture.cpp \
    src/scriptengine.cpp \
    src/mysqlquery.cpp \
    src/report.cpp \
    src/reports.cpp
HEADERS += src/app.h \
    src/dbfactory.h \
    src/gui/guifactory.h \
    src/gui/passwordform.h \
    src/gui/form.h \
    src/gui/connectionform.h \
    src/gui/mainwindow.h \
    src/gui/calendarform.h \
    src/essence.h \
    src/gui/searchparameters.h \
    src/gui/formgrid.h \
    src/gui/formgridsearch.h \
    src/dictionary.h \
    src/dictionaries.h \
    src/gui/mycombobox.h \
    src/reporttemplate.h \
    src/reportengine.h \
    src/gui/formdocument.h \
    src/documents.h \
    src/mysqlrelationaltablemodel.h \
    src/topers.h \
    src/document.h \
    src/table.h \
    src/documenttablemodel.h \
    src/gui/tableview.h \
    src/gui/mynumericitemdelegate.h \
    src/gui/mybooleanitemdelegate.h \
    src/saldo.h \
    src/gui/docparameters.h \
    src/gui/numericedit.h \
    src/gui/myitemdelegate.h \
    src/gui/mylineitemdelegate.h \
    src/definitions.h \
    src/gui/picture.h \
    src/scriptengine.h \
    src/mysqlquery.h \
    src/report.h \
    src/reports.h
RESOURCES += src/resources.qrc

unix:MOC_DIR = ./.moc
win32:MOC_DIR = /.moc

unix:OBJECTS_DIR = ./.obj
win32:OBJECTS_DIR = /.obj

unix:RCC_DIR = ./src
win32:RCC_DIR = /src
