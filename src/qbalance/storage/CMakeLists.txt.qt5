cmake_minimum_required(VERSION 3.13)

set(PROJECTNAME storage)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Sql)
find_package(Qt5Widgets)

aux_source_directory (. DIR_STORAGE_SRCS)
add_library (${PROJECTNAME} ${DIR_STORAGE_SRCS})

qt5_use_modules(${PROJECTNAME} Core Sql Widgets)


