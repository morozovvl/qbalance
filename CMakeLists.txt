PROJECT( qbalance )
 
cmake_minimum_required(VERSION 2.8)

set ( CMAKE_BUILD_TYPE "Release" )
  
add_subdirectory(src/${PROJECT_NAME}) 

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/src/qbalance/LICENSE.GPL")
set (CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")

if (${CMAKE_SYSTEM_NAME} STREQUAL Windows)
  install ( PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/src/${PROJECT_NAME}/${PROJECT_NAME}.exe DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/.. )
else ()
  install ( PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/src/${PROJECT_NAME}/${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/.. )
endif ()

include (InstallRequiredSystemLibraries)

set ( QT_VERSION_MAJOR "4" )
set ( QT_VERSION_MINOR "7" )
set ( QT_VERSION_PATCH "4" )
#set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "My funky project")
#set (CPACK_PACKAGE_VENDOR "Me, myself, and I")
#set (CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
#set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
#set (CPACK_PACKAGE_VERSION_MAJOR "1")
#set (CPACK_PACKAGE_VERSION_MINOR "3")
#set (CPACK_PACKAGE_VERSION_PATCH "2")
#set (CPACK_PACKAGE_install _DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
if (WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  set (CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
  set (CPACK_NSIS_install ED_ICON_NAME "bin\\\\MyExecutable.exe")
  set (CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_install _DIRECTORY} My Famous Project")
  set (CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
  set (CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
  set (CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
  set (CPACK_NSIS_MODif Y_PATH ON)
  install ( TARGETS DESTINATION bin )
  install (FILES
        "${QT_LIBRARY_DIR}/QtCore${QT_VERSION_MAJOR}.dll"
        "${QT_LIBRARY_DIR}/QtXml${QT_VERSION_MAJOR}.dll"
        "${QT_LIBRARY_DIR}/QtTest${QT_VERSION_MAJOR}.dll"
        "${QT_LIBRARY_DIR}/QtGui${QT_VERSION_MAJOR}.dll"
        "${QT_LIBRARY_DIR}/QtNetwork${QT_VERSION_MAJOR}.dll"
        "${QT_LIBRARY_DIR}/QtScript${QT_VERSION_MAJOR}.dll"
        DESTINATION bin
	)

else (WIN32 AND NOT UNIX)
  if (UNIX AND NOT APPLE)
    set (CPACK_STRIP_FILES "bin/${PROJECT_NAME}")
    set (CPACK_SOURCE_STRIP_FILES "")
    install (TARGETS  DESTINATION bin
    )
    foreach (LIB QtCore QtXml QtTest QtGui QtNetwork QtScript)
        install (FILES
            "${QT_LIBRARY_DIR}/lib${LIB}.so.${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}"
            RENAME "lib${LIB}.so.${QT_VERSION_MAJOR}"
            DESTINATION bin
        )
    endforeach (LIB)
endif (UNIX AND NOT APPLE)

endif (WIN32 AND NOT UNIX)
set (CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "My Executable")
include (CPack)
message ( ${QT_VERSION_MAJOR} )