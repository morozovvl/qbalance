PROJECT( qbalance )
 
cmake_minimum_required(VERSION 2.8)

add_subdirectory(./src/qtscriptgenerator)
add_subdirectory(./src/qextserialport)
add_subdirectory(./src/qbalance)

set(CPACK_PACKAGE_NAME "QBalance")
set(CPACK_PACKAGE_VENDOR "Vladimir A.Morozov")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "QBalance - just one more account framework")
set(CPACK_PACKAGE_VERSION "0.0.1")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "QBalance test")

include(CPack)
