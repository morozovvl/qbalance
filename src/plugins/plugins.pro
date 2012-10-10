QT += sql
QT += core
QT += script
QT += gui
QT += xml
QT += network
CONFIG += designer \
    plugin \
    uitools
TARGET = ../../plugins/plugins
TEMPLATE = lib

DEPENDPATH += .
INCLUDEPATH += .

HEADERS += dialogplugin.h \
           docparametersplugin.h \
           mynumericeditplugin.h \
           myplugins.h \
           mytableviewplugin.h \
           pictureplugin.h \
           searchparametersplugin.h \
           tableviewplugin.h \
           ../gui/dialog.h \
           ../gui/docparameters.h \
           ../kernel/app.h \
           ../kernel/dictionaries.h \
           ../kernel/dictionary.h \
           ../kernel/essence.h \
           ../kernel/table.h \
           ../storage/dbfactory.h \
           ../storage/mysqlrelationaltablemodel.h \
           ../engine/scriptengine.h \
           ../engine/sqlqueryclass.h \
           ../engine/sqlrecordclass.h \
           ../engine/sqlfieldclass.h \
           ../engine/reportscriptengine.h \
           ../engine/reportcontext.h \
           ../gui/formgridsearch.h \
           ../gui/formgrid.h \
           ../gui/tableview.h \
           ../gui/myitemdelegate.h \
           ../gui/form.h \
           ../gui/picture.h \
           ../kernel/saldo.h \
           ../kernel/documents.h \
           ../kernel/topers.h \
           ../gui/guifactory.h \
           ../gui/mycombobox.h \
           ../gui/mynumericedit.h \
           ../gui/mytableview.h \
           ../gui/searchparameters.h
SOURCES += dialogplugin.cpp \
           docparametersplugin.cpp \
           mynumericeditplugin.cpp \
           myplugins.cpp \
           mytableviewplugin.cpp \
           pictureplugin.cpp \
           searchparametersplugin.cpp \
           tableviewplugin.cpp \
           ../gui/dialog.cpp \
           ../gui/docparameters.cpp \
           ../kernel/app.cpp \
           ../kernel/dictionaries.cpp \
           ../kernel/dictionary.cpp \
           ../kernel/essence.cpp \
           ../kernel/table.cpp \
           ../storage/dbfactory.cpp \
           ../storage/mysqlrelationaltablemodel.cpp \
           ../engine/scriptengine.cpp \
           ../engine/sqlqueryclass.cpp \
           ../engine/sqlrecordclass.cpp \
           ../engine/sqlfieldclass.cpp \
           ../engine/reportscriptengine.cpp \
           ../engine/reportcontext.cpp \
           ../gui/formgridsearch.cpp \
           ../gui/formgrid.cpp \
           ../gui/tableview.cpp \
           ../gui/myitemdelegate.cpp \
           ../gui/form.cpp \
           ../gui/picture.cpp \
           ../kernel/saldo.cpp \
           ../kernel/documents.cpp \
           ../kernel/topers.cpp \
           ../gui/guifactory.cpp \
           ../gui/mycombobox.cpp \
           ../gui/mynumericedit.cpp \
           ../gui/mytableview.cpp \
           ../gui/searchparameters.cpp


unix:MOC_DIR = ../../.moc
win32:MOC_DIR = ../../.moc

unix:OBJECTS_DIR = ../../.obj
win32:OBJECTS_DIR = ../../.obj

unix:RCC_DIR = ..
win32:RCC_DIR = ..

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
}

