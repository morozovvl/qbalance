# -------------------------------------------------
# Project created by QtCreator 2009-04-25T16:32:03
# -------------------------------------------------

# для профилировщика
#QMAKE_CXXFLAGS_DEBUG += -pg
#QMAKE_LFLAGS_DEBUG += -pg



QT += sql \
      xml \
      core \
      script \
      gui \
      network

CONFIG(debug) {
    DESTDIR = ./
}

TARGET = ../../qbalance
CONFIG += designer \
    plugin \
    uitools
CONFIG -= app_bundle
TEMPLATE = app
#CONFIG += debug


SOURCES += main.cpp \
    kernel/app.cpp \
    storage/dbfactory.cpp \
    gui/passwordform.cpp \
    gui/form.cpp \
    gui/guifactory.cpp \
    gui/connectionform.cpp \
    gui/mainwindow.cpp \
    gui/calendarform.cpp \
    kernel/essence.cpp \
    gui/searchparameters.cpp \
    gui/formgrid.cpp \
    gui/formgridsearch.cpp \
    kernel/dictionary.cpp \
    kernel/dictionaries.cpp \
    gui/mycombobox.cpp \
    report/reportengine.cpp \
    gui/formdocument.cpp \
    kernel/documents.cpp \
    storage/mysqlrelationaltablemodel.cpp \
    kernel/topers.cpp \
    kernel/document.cpp \
    kernel/table.cpp \
    gui/tableview.cpp \
    gui/mynumericitemdelegate.cpp \
    gui/mybooleanitemdelegate.cpp \
    kernel/saldo.cpp \
    gui/docparameters.cpp \
    gui/myitemdelegate.cpp \
    gui/mylineitemdelegate.cpp \
    gui/picture.cpp \
    engine/scriptengine.cpp \
    gui/mynumericedit.cpp \
    report/reports.cpp \
    engine/reportscriptengine.cpp \
    report/ooreportengine.cpp \
    engine/reportcontext.cpp \
    engine/sqlqueryclass.cpp \
    engine/sqlqueryprototype.cpp \
    engine/sqlrecordclass.cpp \
    engine/sqlrecordprototype.cpp \
    engine/sqlfieldclass.cpp \
    engine/sqlfieldprototype.cpp \
    engine/eventloop.cpp \
    engine/documentscriptengine.cpp \
    gui/configform.cpp \
    gui/wizardform.cpp \
    gui/mybuttonlineedit.cpp \
    gui/mybuttonlineedititemdelegate.cpp \
    gui/wizarddictionary.cpp \
    gui/wizardoperation.cpp \
    gui/mytextedit.cpp \
    gui/mysyntaxhighlighter.cpp \
    gui/dialog.cpp \
    gui/progressbar.cpp \
    driverfr/driverfr.cpp \
    gui/mydateitemdelegate.cpp \
    report/ooxmlreportengine.cpp \
    gui/mymdisubwindow.cpp
HEADERS += kernel/app.h \
    storage/dbfactory.h \
    gui/guifactory.h \
    gui/passwordform.h \
    gui/form.h \
    gui/connectionform.h \
    gui/mainwindow.h \
    gui/calendarform.h \
    kernel/essence.h \
    gui/searchparameters.h \
    gui/formgrid.h \
    gui/formgridsearch.h \
    kernel/dictionary.h \
    kernel/dictionaries.h \
    gui/mycombobox.h \
    report/reportengine.h \
    gui/formdocument.h \
    kernel/documents.h \
    storage/mysqlrelationaltablemodel.h \
    kernel/topers.h \
    kernel/document.h \
    kernel/table.h \
    gui/tableview.h \
    gui/mynumericitemdelegate.h \
    gui/mybooleanitemdelegate.h \
    kernel/saldo.h \
    gui/docparameters.h \
    gui/myitemdelegate.h \
    gui/mylineitemdelegate.h \
    definitions.h \
    gui/picture.h \
    engine/scriptengine.h \
    gui/mynumericedit.h \
    report/reports.h \
    engine/reportscriptengine.h \
    report/ooreportengine.h \
    engine/reportcontext.h \
    engine/sqlqueryclass.h \
    engine/sqlqueryprototype.h \
    engine/sqlrecordclass.h \
    engine/sqlrecordprototype.h \
    engine/sqlfieldclass.h \
    engine/sqlfieldprototype.h \
    engine/eventloop.h \
    engine/documentscriptengine.h \
    engine/reportcontextfunctions.h \
    gui/configform.h \
    gui/wizardform.h \
    gui/mybuttonlineedit.h \
    gui/mybuttonlineedititemdelegate.h \
    gui/wizarddictionary.h \
    gui/wizardoperation.h \
    gui/mytextedit.h \
    gui/mysyntaxhighlighter.h \
    gui/dialog.h \
    gui/progressbar.h \
    driverfr/driverfr.h \
    gui/mydateitemdelegate.h \
    report/ooxmlreportengine.h \
    gui/mymdisubwindow.h
RESOURCES += ../../resources.qrc

unix:MOC_DIR = ../../.moc
win32:MOC_DIR = ../../.moc

unix:OBJECTS_DIR = ../../.obj
win32:OBJECTS_DIR = ../../.obj

unix:RCC_DIR = ../qbalance
win32:RCC_DIR = ../qbalance

unix {
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

    INCLUDEPATH += $$(OO_SDK_HOME)/include
    INCLUDEPATH += $$(OO_SDK_HOME)/includecppu
    LIBS += $$(OO_SDK_URE_LIB_DIR)/libuno_cppuhelpergcc3.so.3
    LIBS += $$(OO_SDK_URE_LIB_DIR)/libuno_cppu.so.3
    LIBS += $$(OO_SDK_URE_LIB_DIR)/libuno_salhelpergcc3.so.3
    LIBS += $$(OO_SDK_URE_LIB_DIR)/libuno_sal.so.3

}

windows {
    RC_FILE+=resources.rc
}

OTHER_FILES += \
    ../qbalance.nsi \
    ../generator.pri \
    ../qtbindingsbase.pri \
    ../qtscriptgenerator.bat \
    license.txt










































