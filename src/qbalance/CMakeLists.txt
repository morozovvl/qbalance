cmake_minimum_required (VERSION 2.6)
set (PROJECTNAME qbalance)
project (${PROJECTNAME})
set(CMAKE_AUTOMOC ON)

set (QT_USE_QTXML TRUE)
set (QT_USE_QTSQL TRUE)
set (QT_USE_QTSCRIPT TRUE)
set (QT_USE_QTNETWORK TRUE)
set (QT_USE_QTUITOOLS TRUE)
set (QT_USE_QTDESIGNER TRUE)
find_package (Qt4 REQUIRED)

include_directories(BEFORE ${CMAKE_SOURCE_DIR}/../google-breakpad/src/)
add_subdirectory (crashhandler)
add_subdirectory (engine)
add_subdirectory (gui)
add_subdirectory (kernel)
add_subdirectory (openoffice)
add_subdirectory (plugins)
add_subdirectory (report)
add_subdirectory (serialport)
add_subdirectory (storage)

set (SOURCE_ROOT ./)
aux_source_directory (${SOURCE_ROOT} PROJECT_NAME_SOURCES)

#qt4_wrap_cpp(MOC_SOURCES ${Q_HEADERS})
#qt4_automoc(${Q_SOURCES})


#aux_source_directory ("${SOURCE_ROOT}/*.h" PROJECT_NAME_HDRS)
#aux_source_directory ("${SOURCE_ROOT}/*.cpp" PROJECT_NAME_SRCS)
#set (PROJECT_NAME_RCS ../../resources.qrc)
#qt4_wrap_cpp (PROJECT_NAME_MOC_HDRS ${PROJECT_NAME_HDRS})
#qt4_add_resources (PROJECT_NAME_RCS_SRCS ${PROJECT_NAME_RCS})
#add_executable ( ${PROJECT_NAME} WIN32 ${PROJECT_NAME_MOC_HDRS} ${PROJECT_NAME_SRCS} ${PROJECT_NAME_RCS_SRCS} ${PROJECT_NAME_SOURCES} )
#target_link_libraries ( ${PROJECT_NAME} ${QT_LIBRARIES} )
#qt4_add_resources(PROJECT_NAME_RCS_SRCS ${PROJECT_NAME_RCS} ) 

set(qbalance_USE_STATIC_LIBS ON)
set(qbalance_USE_MULTITHREADED ON)

#find_package(${PROJECTNAME} COMPONENTS kernel gui crashhandler openoffice plugins report serialport storage REQUIRED)

add_executable (${PROJECTNAME} ${PROJECT_NAME_SOURCES})
#target_link_libraries(${PROJECTNAME} ${qbalance_LIBRARIES} QtScript QtSql QtNetwork QtUiTools QtXml QtGui QtCore QtDesigner  ${QT_LIBRARIES})
target_link_libraries(${PROJECTNAME} ${qbalance_LIBRARIES} ${QT_LIBRARIES})
