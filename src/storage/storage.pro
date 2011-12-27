#-------------------------------------------------
#
# Project created by QtCreator 2011-09-16T13:43:05
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = storage
TEMPLATE = lib

DEFINES += STORAGE_LIBRARY

SOURCES += storage.cpp

HEADERS += storage.h\
        storage_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE4D0F317
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = storage.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
