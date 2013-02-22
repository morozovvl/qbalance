unix:TARGET = ../../plugins/drvfr
win32:TARGET = ../../../plugins/drvfr

unix:MOC_DIR = ../../.moc/drvfr
win32:MOC_DIR = ../../.moc/drvfr

unix:OBJECTS_DIR = ../../.obj/drvfr
win32:OBJECTS_DIR = ../../.obj/drvfr

DEFINES += MYSHAREDLIB_LIBRARY
SOURCES += conn.cpp interface.cpp options.cpp
HEADERS += drvfr.h conn.h errdefs.h interface.h options.h \
    mysharedlib_global.h
TEMPLATE =lib
CONFIG  += warn_on release
DBFILE   = /root/drvfr/drvfr.db
LANGUAGE = C++
#DESCRIPTION = This is an Shtrih-M's Fiscal Registrator

