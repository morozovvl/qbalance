#-------------------------------------------------
#
# Project created by QtCreator 2011-10-10T09:47:02
#
#-------------------------------------------------

QT       -= gui

TARGET = report
TEMPLATE = lib

DEFINES += REPORT_LIBRARY

SOURCES += report.cpp

HEADERS += report.h\
        report_global.h

symbian {
    #Symbian specific definitions
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE0A1F4C2
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = report.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}
