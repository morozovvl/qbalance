cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

SET ( CMAKE_CXX_FLAGS "-ludev" )

find_package (Qt4 REQUIRED)
include(${QT_USE_FILE})

add_subdirectory(src/qbalance/bankterminal)
add_subdirectory(src/qbalance/barcodereader)
add_subdirectory(src/qbalance/cardcodereader)
add_subdirectory(src/qbalance/driverfr)
add_subdirectory(src/qbalance/emailclient)
add_subdirectory(src/qbalance)

set(CMAKE_AUTOMOC OFF)
add_subdirectory(src/qbalance/plugins)


