cmake_minimum_required(VERSION 3.13)

set(PROJECTNAME openoffice)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)

aux_source_directory (. DIR_OPENOFFICE_SRCS)
add_library (${PROJECTNAME} ${DIR_OPENOFFICE_SRCS})

qt5_use_modules(${PROJECTNAME} Core)


