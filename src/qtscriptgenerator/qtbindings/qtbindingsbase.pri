TEMPLATE = lib
DEPENDPATH += .
INCLUDEPATH += .
DESTDIR = $$PWD/../../../plugins
QT += script
CONFIG += debug_and_release
GENERATEDCPP = $$PWD/../generated_cpp
TARGET=$$qtLibraryTarget($$TARGET)
