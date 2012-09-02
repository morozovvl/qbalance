QT += sql
QT += core
QT += script
QT += gui
QT += xml
CONFIG += designer \
    plugin
CONFIG += debug
TARGET = ../../plugins/plugins
TEMPLATE = lib
HEADERS = tableviewplugin.h \
    ../gui/tableview.h \
    pictureplugin.h \
    ../gui/picture.h \
    myplugins.h \
    searchparametersplugin.h \
    ../gui/searchparameters.h \
    ../gui/mycombobox.h \
    docparametersplugin.h \
    ../gui/docparameters.h \
    mynumericeditplugin.h \
    ../gui/mynumericedit.h \
    ../gui/mynumericitemdelegate.h \
    ../gui/myitemdelegate.h \
    ../gui/dialog.h \
    dialogplugin.h
SOURCES = tableviewplugin.cpp \
    ../gui/tableview.cpp \
    pictureplugin.cpp \
    ../gui/picture.cpp \
    myplugins.cpp \
    searchparametersplugin.cpp \
    ../gui/searchparameters.cpp \
    ../gui/mycombobox.cpp \
    docparametersplugin.cpp \
    ../gui/docparameters.cpp \
    mynumericeditplugin.cpp \
    ../gui/mynumericedit.cpp \
    ../gui/mynumericitemdelegate.cpp \
    ../gui/myitemdelegate.cpp \
    ../gui/dialog.cpp \
    dialogplugin.cpp

unix:MOC_DIR = ../../.moc
win32:MOC_DIR = ../../.moc

unix:OBJECTS_DIR = ../../.obj
win32:OBJECTS_DIR = ../../.obj

unix:RCC_DIR = ../src
win32:RCC_DIR = ../src





