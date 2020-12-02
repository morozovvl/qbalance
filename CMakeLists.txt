cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(READ "src/qbalance/version.h" ver)
string(REPLACE "#define BUILD_NUMBER " "" ver ${ver})
set(VERSION ver)
set(CPACK_PACKAGE_VERSION ${VERSION})

set(CPACK_PACKAGE_RELEASE 1)

set (PROJECT0 qbalance)
set (PROJECT1 qb_main)

SET (CMAKE_CXX_FLAGS "-ludev" )

find_package (Qt4 REQUIRED)
include(${QT_USE_FILE})

add_subdirectory(src/qbalance/bankterminal)
add_subdirectory(src/qbalance/barcodereader)
add_subdirectory(src/qbalance/cardcodereader)
add_subdirectory(src/qbalance/driverfr)
add_subdirectory(src/qbalance/emailclient)
add_subdirectory(src/qbalance/odfpreviewlib)
add_subdirectory(src/qbalance)

set(CMAKE_AUTOMOC OFF)
add_subdirectory(src/qbalance/plugins)

#set(CPACK_BINARY_RPM ON)
#set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_GENERATOR "RPM")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_PACKAGE_NAME ${PROJECT0})
set(CPACK_PACKAGE_CONTACT "NoName")
set(CPACK_PACKAGE_VENDOR "Some Vendor")
#set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")

#install(TARGETS ${PROJECT0} ${PROJECT1} DESTINATION applications/${PROJECT0})
#install(FILES qt.conf resources.qrc DESTINATION applications/${PROJECT0})
#install(DIRECTORY plugins DESTINATION applications/${PROJECT0} FILES_MATCHING PATTERN "*.so*")
#install(DIRECTORY resources DESTINATION applications/${PROJECT0} FILES_MATCHING PATTERN "*.*")

include(CPack)


