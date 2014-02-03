TARGET = qtscript_xmlpatterns
include(../qtbindingsbase.pri)

QT -= gui
QT += xmlpatterns network

SOURCES += $$GENERATEDCPP/com_trolltech_qt_xmlpatterns/plugin.cpp
HEADERS += $$GENERATEDCPP/com_trolltech_qt_xmlpatterns/plugin.h

include($$GENERATEDCPP/com_trolltech_qt_xmlpatterns/com_trolltech_qt_xmlpatterns.pri)
