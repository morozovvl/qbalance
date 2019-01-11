cmake_minimum_required(VERSION 3.13)

file (STRINGS "version.h" BUILD_NUMBER_STRING)
string(REGEX MATCH "[0-9]+\\.[0-9]+" BUILD_NUMBER ${BUILD_NUMBER_STRING})

#set(VERSION ${BUILD_NUMBER})
set (PROJECT0 qbalance)
set (PROJECT1 qb_main)

project (${PROJECT0})

find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Sql)
find_package(Qt5Script)
find_package(Qt5Xml)
find_package(Qt5Network)
find_package(Qt5UiTools)
find_package(Qt5SerialPort)

add_subdirectory(engine)
add_subdirectory(gui)
add_subdirectory(kernel)
add_subdirectory(storage)
add_subdirectory(report)
add_subdirectory(openoffice)
add_subdirectory(serialport)
#add_subdirectory(startup)

set(SUBDIRS0 startup)
set(SUBDIRS1 kernel gui report openoffice storage engine serialport)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})

#add_executable(${PROJECT0} ${SUBDIRS0})
#target_link_libraries(${PROJECT0} ${SUBDIRS0} Qt5::Core)

add_executable(${PROJECT1} main.cpp ${SUBDIRS1} ../../resources.qrc)
target_link_libraries(${PROJECT1} ${SUBDIRS1} Qt5::Widgets Qt5::Core Qt5::Sql Qt5::Script Qt5::Xml Qt5::Network Qt5::UiTools Qt5::SerialPort)

set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_PACKAGE_VERSION ${BUILD_NUMBER})
set(CPACK_PACKAGE_NAME ${PROJECT0})
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "MorozovVladimir@mail.ru")
set(CPACK_PACKAGE_VENDOR "Vladimir A. Morozov")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")

#install(TARGETS ${PROJECT0} ${PROJECT1} DESTINATION applications/${PROJECT0})
#install(DIRECTORY ../../plugins DESTINATION applications/${PROJECT0} FILES_MATCHING PATTERN "*/plugins/*.so")
#install(DIRECTORY ../../plugins DESTINATION applications/${PROJECT0} FILES_MATCHING PATTERN "*/plugins/designer/*.so")
#file(GLOB INITDB_FILES "../../initdb*.sql")
#install(FILES ${INITDB_FILES} DESTINATION applications/${PROJECT0})

#include(CPack)
