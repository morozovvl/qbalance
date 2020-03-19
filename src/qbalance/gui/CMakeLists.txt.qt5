cmake_minimum_required(VERSION 3.13)

set(PROJECTNAME gui)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Widgets)

aux_source_directory (. DIR_GUI_SRCS)
add_library (${PROJECTNAME} ${DIR_GUI_SRCS})

qt5_use_modules(${PROJECTNAME} Core Widgets)


