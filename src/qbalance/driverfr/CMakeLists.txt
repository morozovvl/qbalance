cmake_minimum_required(VERSION 3.13)

set(CMAKE_BUILD_TYPE "Release")
set(PROJECTNAME driverfr)
project(${PROJECTNAME})
find_package(Qt5Widgets)
#include(${QT_USE_FILE})
set(SOURCE_ROOT ./)
aux_source_directory (${SOURCE_ROOT} SOURCES)
set(LIBRARY_OUTPUT_PATH ${SOURCE_ROOT}/../../../../plugins)
add_library (${PROJECTNAME} MODULE ${SOURCES})

qt5_use_modules(${PROJECTNAME} Widgets)
