TEMPLATE     = lib
DEPENDPATH  += .
INCLUDEPATH += .
DESTDIR      = $$PWD/../plugins/script
QT          += script
CONFIG      += debug_and_release plugin hide_symbols

GENERATEDCPP = $$PWD/../generated_cpp
TARGET       = $$qtLibraryTarget($$TARGET)
