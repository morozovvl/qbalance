greaterThan(QT_MAJOR_VERSION, 4) {
    QT += webkitwidgets
}
else {
    QT += webkit
}

QT    += network
TARGET = qtscript_webkit

include(../qtbindingsbase.pri)

SOURCES += $$GENERATEDCPP/com_trolltech_qt_webkit/plugin.cpp
HEADERS += $$GENERATEDCPP/com_trolltech_qt_webkit/plugin.h

include($$GENERATEDCPP/com_trolltech_qt_webkit/com_trolltech_qt_webkit.pri)
