TARGET = qtscript_opengl
include(../qtbindingsbase.pri)

QT += opengl

SOURCES += $$GENERATEDCPP/com_trolltech_qt_opengl/plugin.cpp
HEADERS += $$GENERATEDCPP/com_trolltech_qt_opengl/plugin.h

include($$GENERATEDCPP/com_trolltech_qt_opengl/com_trolltech_qt_opengl.pri)
