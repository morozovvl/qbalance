TARGET = qtscript_svg
include(../qtbindingsbase.pri)

QT += svg

SOURCES += $$GENERATEDCPP/com_trolltech_qt_svg/plugin.cpp
HEADERS += $$GENERATEDCPP/com_trolltech_qt_svg/plugin.h

include($$GENERATEDCPP/com_trolltech_qt_svg/com_trolltech_qt_svg.pri)
