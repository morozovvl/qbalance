#-------------------------------------------------
#
# Project created by QtCreator 2011-09-16T13:37:52
#
#-------------------------------------------------

TARGET = gui
TEMPLATE = lib

DEFINES += GUI_LIBRARY

SOURCES += gui.cpp

HEADERS += gui.h\
        gui_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE599000F
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = gui.dll
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
