#-------------------------------------------------
#
# Project created by QtCreator 2011-09-16T13:54:32
#
#-------------------------------------------------

QT       += script xml

QT       -= gui

TARGET = engine
TEMPLATE = lib

DEFINES += ENGINE_LIBRARY

SOURCES += engine.cpp

HEADERS += engine.h\
        engine_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE52FE922
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = engine.dll
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
