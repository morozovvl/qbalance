cmake_minimum_required(VERSION 3.13)

set(PROJECTNAME serialport)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core)

aux_source_directory (. DIR_SERIALPORT_SRCS)
#aux_source_directory (../../qextserialport/src DIR_EXTSERIALPORT_SRCS)

add_library (${PROJECTNAME} ${DIR_SERIALPORT_SRCS})
qt5_use_modules(${PROJECTNAME} Core)


