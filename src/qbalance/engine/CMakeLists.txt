cmake_minimum_required(VERSION 3.13)

set(PROJECTNAME engine)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Script)
find_package(Qt5Widgets)

aux_source_directory (. DIR_ENGINE_SRCS)
add_library (${PROJECTNAME} ${DIR_ENGINE_SRCS})

qt5_use_modules(${PROJECTNAME} Core Script Widgets)


