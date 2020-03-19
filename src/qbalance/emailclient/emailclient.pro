CONFIG += plugin \
          core

unix:TARGET = ../../../plugins/emailclient
win32:TARGET = ../../../../plugins/emailclient

TEMPLATE = lib

DEPENDPATH += .
INCLUDEPATH += .

HEADERS += emailclient.h \
            emailclientplugin.h
SOURCES += emailclient.cpp \
            emailclientplugin.cpp

unix:MOC_DIR = ../../../.moc
win32:MOC_DIR = ../../../.moc

unix:OBJECTS_DIR = ../../../.obj
win32:OBJECTS_DIR = ../../../.obj

unix:RCC_DIR = ../..
win32:RCC_DIR = ../..

