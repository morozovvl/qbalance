TARGET = qtscript_core
include(../qtbindingsbase.pri)

SOURCES += $$GENERATEDCPP/com_trolltech_qt_core/plugin.cpp
HEADERS += qtscriptconcurrent.h $$GENERATEDCPP/com_trolltech_qt_core/plugin.h

include($$GENERATEDCPP/com_trolltech_qt_core/com_trolltech_qt_core.pri)

