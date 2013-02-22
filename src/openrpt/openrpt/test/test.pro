TEMPLATE = app
CONFIG += qt warn_on
INCLUDEPATH += ../common ../../common ../../../openrpt-build-desktop/common ../renderer ../../report

TARGET = test
unix:TARGET = test

OBJECTS_DIR = tmp
MOC_DIR     = tmp
UI_DIR      = tmp

LIBS += -L../../lib -lrenderer -lcommon -lDmtx_Library -lreport

win32-msvc* {
  PRE_TARGETDEPS += ../../lib/common.lib   \
                    ../../lib/renderer.lib
} else {
  PRE_TARGETDEPS += ../../lib/libcommon.a   \
                    ../../lib/librenderer.a \
                    ../../lib/libreport.a \
}

DESTDIR = ../../bin

# Input
FORMS   += mainwindow.ui 

HEADERS += mainwindow.h 

SOURCES += main.cpp \
           mainwindow.cpp 

QT += xml sql

