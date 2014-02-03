TARGET = qtscript_phonon
include(../qtbindingsbase.pri)

QT += phonon

SOURCES += $$GENERATEDCPP/com_trolltech_qt_phonon/plugin.cpp
HEADERS += $$GENERATEDCPP/com_trolltech_qt_phonon/plugin.h

include($$GENERATEDCPP/com_trolltech_qt_phonon/com_trolltech_qt_phonon.pri)
