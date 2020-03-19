#cmake_minimum_required(VERSION 3.0)

set(PROJECT qextserialport)
project(${PROJECT})

SET (CMAKE_AUTOMOC ON)
SET (QT_USE_QTPLUGINS TRUE)
set (QT_USE_QTXML TRUE)
set (QT_USE_QTSQL TRUE)
set (QT_USE_QTSCRIPT TRUE)
set (QT_USE_QTNETWORK TRUE)
set (QT_USE_QTUITOOLS TRUE)
set (QT_USE_QTDESIGNER TRUE)
find_package (Qt4 REQUIRED COMPONENTS)
include(${QT_USE_FILE})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

set (SOURCES
    ./src/qextserialenumerator.cpp
#    ./src/qextserialenumerator_osx.cpp
#    ./src/qextserialenumerator_win.cpp
    ./src/qextserialport_unix.cpp
    ./src/qextserialenumerator_linux.cpp
    ./src/qextserialenumerator_unix.cpp
    ./src/qextserialport.cpp
    ./src/moc_qextserialport.cxx
#    ./src/qextserialport_win.cpp
)

set (HEADERS
    ./src/qextserialenumerator.h
    ./src/qextserialport_global.h
    ./src/qextserialport_p.h
    ./src/qextserialport.h
#    ./src/moc_qextserialport.cxx
)


qt4_wrap_cpp (HEADERS_MOC ${HEADERS})

#add_definitions(${QT_DEFINITIONS})
#add_definitions(-DQT_STATICPLUGIN) 
#add_definitions(-DQDESIGNER_EXPORT_WIDGETS)

#add_executable(${PROJECT}
#    ${SOURCES}
#    ${HEADERS_MOC}
#    ${RESOURCES_RCC}
#)

add_library (${PROJECT} ${SOURCES} ${HEADERS} ${HEADERS_MOC})

target_link_libraries(${PROJECT}
    ${QT_LIBRARIES}
)
