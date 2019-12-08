# -------------------------------------------------
# Project created by QtCreator 2009-04-25T16:32:03
# -------------------------------------------------

# для профилировщика
#QMAKE_CXXFLAGS_DEBUG += -pg
#QMAKE_LFLAGS_DEBUG += -pg

QMAKE_CXXFLAGS += -std=c++0x

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0

#greaterThan(QT_MAJOR_VERSION, 5)
#{
#    QT += sql \
#          xml \
#          core \
#          gui \
#          network \
#          script \
#          printsupport \
#          widgets \
#          uitools \
#          serialport \
#          qml
#}

#greaterThan(QT_MAJOR_VERSION, 4)
#{
    QT += sql \
          xml \
          core \
          gui \
          network \
          script \
          printsupport \
          widgets
    include(../qextserialport/src/qextserialport.pri)
    CONFIG += designer \
              uitools
#}


APP_NAME = qb_main

TARGET = ../../$${APP_NAME}

DEFINES += APPLICATION_NAME=\\\"$${APP_NAME}\\\"

CONFIG -= app_bundle
#CONFIG += static

TEMPLATE = app


SOURCES += main.cpp \
    gui/passwordform.cpp \
    gui/form.cpp \
    gui/guifactory.cpp \
    gui/connectionform.cpp \
    gui/mainwindow.cpp \
    gui/calendarform.cpp \
    gui/searchparameters.cpp \
    gui/formgrid.cpp \
    gui/formgridsearch.cpp \
    gui/mycombobox.cpp \
    gui/formdocument.cpp \
    gui/formdocuments.cpp \
    gui/tableview.cpp \
    gui/mynumericitemdelegate.cpp \
    gui/mybooleanitemdelegate.cpp \
    gui/docparameters.cpp \
    gui/myitemdelegate.cpp \
    gui/mylineitemdelegate.cpp \
    gui/picture.cpp \
    gui/mynumericedit.cpp \
    gui/configform.cpp \
    gui/wizardform.cpp \
    gui/mybuttonlineedit.cpp \
    gui/mybuttonlineedititemdelegate.cpp \
    gui/wizarddictionary.cpp \
    gui/wizardoperation.cpp \
    gui/mytextedit.cpp \
    gui/mysyntaxhighlighter.cpp \
    gui/dialog.cpp \
    gui/mydateitemdelegate.cpp \
    gui/messagewindow.cpp \
    gui/myprogressdialog.cpp \
    kernel/app.cpp \
    kernel/essence.cpp \
    kernel/dictionary.cpp \
    kernel/dictionaries.cpp \
    kernel/documents.cpp \
    kernel/topers.cpp \
    kernel/document.cpp \
    kernel/table.cpp \
    kernel/saldo.cpp \
    kernel/tcpserver.cpp \
    kernel/tcpclient.cpp \
    storage/mysqlrelationaltablemodel.cpp \
    storage/dbfactory.cpp \
    report/ooreportengine.cpp \
    report/reportengine.cpp \
    report/ooxmlreportengine.cpp \
    engine/scriptengine.cpp \
    engine/reportcontext.cpp \
    engine/sqlqueryclass.cpp \
    engine/sqlqueryprototype.cpp \
    engine/sqlrecordclass.cpp \
    engine/sqlrecordprototype.cpp \
    engine/sqlfieldclass.cpp \
    engine/sqlfieldprototype.cpp \
    engine/eventloop.cpp \
    engine/documentscriptengine.cpp \
#    engine/qfileinfoprototype.cpp \
    openoffice/ooxmlengine.cpp \
    serialport/qmyextserialport.cpp \
    gui/myvalueeditor.cpp \
    kernel/updates.cpp \
    gui/myuiloader.cpp \
    storage/postgresdbfactory.cpp \
    storage/sqlitedbfactory.cpp \
    kernel/report.cpp \
    kernel/reports.cpp

HEADERS +=  gui/passwordform.h \
    gui/form.h \
    gui/guifactory.h \
    gui/connectionform.h \
    gui/mainwindow.h \
    gui/calendarform.h \
    gui/searchparameters.h \
    gui/formgrid.h \
    gui/formgridsearch.h \
    gui/mycombobox.h \
    gui/formdocument.h \
    gui/formdocuments.h \
    gui/tableview.h \
    gui/mynumericitemdelegate.h \
    gui/mybooleanitemdelegate.h \
    gui/docparameters.h \
    gui/myitemdelegate.h \
    gui/mylineitemdelegate.h \
    gui/picture.h \
    gui/mynumericedit.h \
    gui/configform.h \
    gui/wizardform.h \
    gui/mybuttonlineedit.h \
    gui/mybuttonlineedititemdelegate.h \
    gui/wizarddictionary.h \
    gui/wizardoperation.h \
    gui/mytextedit.h \
    gui/mysyntaxhighlighter.h \
    gui/dialog.h \
    gui/mydateitemdelegate.h \
    gui/messagewindow.h \
    gui/myprogressdialog.h \
    kernel/app.h \
    kernel/essence.h \
    kernel/dictionary.h \
    kernel/dictionaries.h \
    kernel/documents.h \
    kernel/topers.h \
    kernel/document.h \
    kernel/table.h \
    kernel/saldo.h \
    kernel/tcpserver.h \
    kernel/tcpclient.h \
    storage/mysqlrelationaltablemodel.h \
    storage/dbfactory.h \
    report/ooreportengine.h \
    report/reportengine.h \
    report/ooxmlreportengine.h \
    engine/scriptengine.h \
    engine/reportcontext.h \
    engine/sqlqueryclass.h \
    engine/sqlqueryprototype.h \
    engine/sqlrecordclass.h \
    engine/sqlrecordprototype.h \
    engine/sqlfieldclass.h \
    engine/sqlfieldprototype.h \
    engine/eventloop.h \
    engine/documentscriptengine.h \
#    engine/qfileinfoprototype.h \
    openoffice/ooxmlengine.h \
    serialport/qmyextserialport.h \
    gui/myvalueeditor.h \
    engine/reportcontextfunctions.h \
    mpreal.h \
    fixed.h \
    storage/filetype.h \
    kernel/configvars.h \
    kernel/updates.h \
    gui/myuiloader.h \
    version.h \
    storage/postgresdbfactory.h \
    storage/sqlitedbfactory.h \
    storage/mymultilist.h \
    kernel/report.h \
    kernel/reports.h


RESOURCES += ../../resources.qrc


unix:MOC_DIR = ../../.moc
win32:MOC_DIR = ../../.moc

unix:OBJECTS_DIR = ../../.obj
win32:OBJECTS_DIR = ../../.obj

unix:RCC_DIR = ../qbalance
win32:RCC_DIR = ../qbalance

unix {
# INCLUDEPATH = ../google-breakpad/src
# HEADERS += crashhandler/crashhandler.h
# SOURCES += crashhandler/crashhandler.cpp
# LIBS += ../google-breakpad/src/client/linux/libbreakpad_client.a
 isEmpty(PREFIX) {
  PREFIX =   /usr
  }
  BINDIR =   $$PREFIX/bin
  DATAROOT =   $$PREFIX/share
  DESKTOPDIR =   $$DATAROOT/applications
  PIXMAPSDIR =   $$DATAROOT/pixmaps
 target.path =  $$BINDIR
 desktop.path =  $$DESKTOPDIR
 desktop.files =  qbalance.desktop
 icons.path =  $$PIXMAPSDIR
 icons.files =  qbalance.png
 INSTALLS +=  target  desktop  icons
# LIBS += ../../lib/libqextserialport.so
    LIBS += /usr/lib64/libsqlite3.so
}

windows {
#    RC_FILE+=resources.rc
#    LIBS += ../../qextserialport1.dll
    LIBS += ../../sqlite3.dll
}

OTHER_FILES += \
    ../qbalance.nsi \
    ../generator.pri \
    ../qtbindingsbase.pri \
    ../qtscriptgenerator.bat \
    license.txt \
    ../../README

#LIBS +=  ../../lib64/libmpfr.so
