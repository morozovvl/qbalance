#cmake_minimum_required(VERSION 3.13)
#set(VERSION "0.19")
#set (PROJECT0 qbalance)
#set (PROJECT1 qb_main)

project (${PROJECT0})

find_library(LIB_SQLITE3 sqlite3 libsqlite3.so)

add_subdirectory(engine)
add_subdirectory(gui)
add_subdirectory(kernel)
add_subdirectory(storage)
add_subdirectory(report)
add_subdirectory(openoffice)
add_subdirectory(serialport)
add_subdirectory(startup)
add_subdirectory(odspreviewlib)


set(SUBDIRS0 startup)
set(SUBDIRS1 kernel gui report openoffice storage engine serialport odspreviewlib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})

add_executable(${PROJECT0} ${SUBDIRS0})
target_link_libraries(${PROJECT0} ${SUBDIRS0} Qt4::QtCore)

add_executable(${PROJECT1} main.cpp ${SUBDIRS1} ../../resources.qrc ${LIB_SQLITE3})
target_link_libraries(${PROJECT1} ${SUBDIRS1} Qt4::QtGui Qt4::QtCore Qt4::QtSql Qt4::QtScript Qt4::QtXml Qt4::QtNetwork Qt4::QtUiTools)

