include(generator.pri)

# Input
HEADERS += \
        generatorsetqtscript.h \
        metaqtscriptbuilder.h \
        metaqtscript.h \
        classgenerator.h \
        shellgenerator.h \
        shellimplgenerator.h \
        shellheadergenerator.h \
        setupgenerator.h \
        docgenerator.h
   
SOURCES += \
        generatorsetqtscript.cpp \
        metaqtscriptbuilder.cpp \
        metaqtscript.cpp \
        classgenerator.cpp \
        shellgenerator.cpp \
        shellimplgenerator.cpp \
        shellheadergenerator.cpp \
        setupgenerator.cpp \
        docgenerator.cpp

CONFIG -= debug
CONFIG += release

#unix:MOC_DIR = ../../../.moc
#win32:MOC_DIR = ../../../.moc

#unix:OBJECTS_DIR = ../../../.obj
#win32:OBJECTS_DIR = ../../../.obj
