QT += sql
QT += core
QT += script
QT += gui
QT += xml
QT += network
CONFIG += designer \
    plugin \
    uitools
CONFIG += debug

unix:TARGET = ../../../plugins/designer/plugins
win32:TARGET = ../../../../plugins/designer/plugins

TEMPLATE = lib

DEPENDPATH += .
INCLUDEPATH += .

HEADERS += dialogplugin.h \
           docparametersplugin.h \
           mynumericeditplugin.h \
           myplugins.h \
           pictureplugin.h \
           searchparametersplugin.h \
           tableviewplugin.h \
           ../gui/docparameters.h \
           ../gui/tableview.h \
           ../gui/picture.h \
           ../gui/dialog.h \
           ../gui/mycombobox.h \
           ../gui/mynumericedit.h \
           ../gui/myitemdelegate.h \
           ../gui/mynumericitemdelegate.h \
           ../gui/mybooleanitemdelegate.h \
           ../gui/mylineitemdelegate.h \
           ../gui/mydateitemdelegate.h \
           ../gui/searchparameters.h
SOURCES += dialogplugin.cpp \
           docparametersplugin.cpp \
           mynumericeditplugin.cpp \
           myplugins.cpp \
           pictureplugin.cpp \
           searchparametersplugin.cpp \
           tableviewplugin.cpp \
           ../gui/docparameters.cpp \
           ../gui/tableview.cpp \
           ../gui/picture.cpp \
           ../gui/dialog.cpp \
           ../gui/mycombobox.cpp \
           ../gui/mynumericedit.cpp \
           ../gui/myitemdelegate.cpp \
           ../gui/mynumericitemdelegate.cpp \
           ../gui/mybooleanitemdelegate.cpp \
           ../gui/mylineitemdelegate.cpp \
           ../gui/mydateitemdelegate.cpp \
           ../gui/searchparameters.cpp


unix:MOC_DIR = ../../../.moc
win32:MOC_DIR = ../../../.moc

unix:OBJECTS_DIR = ../../../.obj
win32:OBJECTS_DIR = ../../../.obj

unix:RCC_DIR = ../..
win32:RCC_DIR = ../..

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



