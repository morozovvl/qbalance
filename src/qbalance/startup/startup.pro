#-------------------------------------------------
#
# Project created by QtCreator 2018-09-03T10:07:18
#
#-------------------------------------------------

QT       += core

QT       -= gui

unix:TARGET = ../../../qbalance
win32:TARGET = ../../../../qbalance

#CONFIG  += console
CONFIG	+= release
CONFIG  -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

unix:MOC_DIR = ../../../.moc
win32:MOC_DIR = ../../../.moc

unix:OBJECTS_DIR = ../../../.obj
win32:OBJECTS_DIR = ../../../.obj

unix:RCC_DIR = ../..
win32:RCC_DIR = ../..

windows {
    RC_FILE+=resources.rc
}
