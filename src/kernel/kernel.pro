#-------------------------------------------------
#
# Project created by QtCreator 2011-09-16T13:34:38
#
#-------------------------------------------------

QT       -= gui

TARGET = kernel
TEMPLATE = lib

DEFINES += KERNEL_LIBRARY

SOURCES += kernel.cpp

HEADERS += kernel.h\
        kernel_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE4A4554E
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = kernel.dll
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
