cmake_minimum_required(VERSION 3.0)

set(PROJECT plugins)
project(${PROJECT})


SET (CMAKE_AUTOMOC ON)
SET (QT_USE_QTPLUGINS TRUE)
set (QT_USE_QTXML TRUE)
set (QT_USE_QTSQL TRUE)
set (QT_USE_QTSCRIPT TRUE)
set (QT_USE_QTNETWORK TRUE)
set (QT_USE_QTUITOOLS TRUE)
set (QT_USE_QTDESIGNER TRUE)
find_package (Qt4 REQUIRED)
include(${QT_USE_FILE})

# Files to insert
set (SOURCES
    dialogplugin.cpp  
    docparametersplugin.cpp  
    mynumericeditplugin.cpp  
    myplugins.cpp  
    pictureplugin.cpp  
    searchparametersplugin.cpp  
    tableviewplugin.cpp
)

set (HEADERS
    dialogplugin.h  
    docparametersplugin.h  
    mynumericeditplugin.h  
    myplugins.h  
    pictureplugin.h  
    searchparametersplugin.h  
    tableviewplugin.h
)

#set (MOCS
#    ./build/moc_dialogplugin.cpp  
#    ./build/moc_docparametersplugin.cpp  
#    ./build/moc_mynumericeditplugin.cpp  
#    ./build/moc_myplugins.cpp  
#    ./build/moc_pictureplugin.cpp  
#    ./build/moc_searchparametersplugin.cpp  
#    ./build/moc_tableviewplugin.cpp
#)


qt4_wrap_cpp (HEADERS_MOC ${HEADERS})
qt4_add_resources(RESOURCES_RCC ${RESOURCES})

include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_STATICPLUGIN) 
add_definitions(-DQDESIGNER_EXPORT_WIDGETS)

#add_executable(${PROJECT}
#    ${SOURCES}
#    ${HEADERS_MOC}
#    ${RESOURCES_RCC}
#)

add_library (${PROJECT} STATIC ${SOURCES} ${HEADERS_MOC} ${RESOURCES_RCC})

target_link_libraries(${PROJECT}
    ${QT_LIBRARIES}
)
