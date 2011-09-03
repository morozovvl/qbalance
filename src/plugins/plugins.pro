QT += sql
QT += core
QT += script
QT += gui
QT += xml
CONFIG += designer \
    plugin
CONFIG += release
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
    numericeditplugin.h \
    ../gui/numericedit.h \
    ../gui/mynumericitemdelegate.h \
    ../gui/myitemdelegate.h
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
    numericeditplugin.cpp \
    ../gui/numericedit.cpp \
    ../gui/mynumericitemdelegate.cpp \
    ../gui/myitemdelegate.cpp
