cmake_minimum_required(VERSION 3.13)

set(PROJECTNAME kernel)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5UiTools)

aux_source_directory (. DIR_KERNEL_SRCS)
add_library (${PROJECTNAME} ${DIR_KERNEL_SRCS})

qt5_use_modules(${PROJECTNAME} Core Widgets UiTools)


