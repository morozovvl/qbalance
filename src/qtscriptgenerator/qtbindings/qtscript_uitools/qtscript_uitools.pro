greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets uitools
}
else {
    CONFIG += uitools
}

TARGET = qtscript_uitools

include(../qtbindingsbase.pri)

SOURCES += $$GENERATEDCPP/com_trolltech_qt_uitools/plugin.cpp
HEADERS += $$GENERATEDCPP/com_trolltech_qt_uitools/plugin.h

include($$GENERATEDCPP/com_trolltech_qt_uitools/com_trolltech_qt_uitools.pri)
