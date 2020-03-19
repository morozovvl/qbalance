cmake_minimum_required(VERSION 3.13)

set(CMAKE_AUTOMOC ON)
find_package(Qt5Core)

aux_source_directory (. DIR_STARTUP_SRCS)
add_library (startup ${DIR_STARTUP_SRCS})
qt5_use_modules(startup Core)