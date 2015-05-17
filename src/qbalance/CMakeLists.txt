cmake_minimum_required(VERSION 3.0)
set ( CMAKE_BUILD_TYPE "Release" )

find_package ( Qt4 REQUIRED )

set ( QT_USE_QTXML TRUE )
set ( QT_USE_QTSQL TRUE )
set ( QT_USE_QTSCRIPT TRUE )
set ( QT_USE_QTNETWORK TRUE )
set ( QT_USE_QTUITOOLS TRUE )

include ( ${QT_USE_FILE} )

set ( PROJECT_NAME_SRCS
    ./main.cpp
    
    ./kernel/app.cpp
    ./kernel/essence.cpp
    ./kernel/dictionary.cpp
    ./kernel/dictionaries.cpp
    ./kernel/documents.cpp
    ./kernel/topers.cpp
    ./kernel/document.cpp
    ./kernel/table.cpp
    ./kernel/saldo.cpp
    ./kernel/barcodereader.cpp
    ./kernel/tcpserver.cpp
    ./kernel/tcpclient.cpp

    ./gui/passwordform.cpp
    ./gui/form.cpp
    ./gui/guifactory.cpp
    ./gui/connectionform.cpp
    ./gui/mainwindow.cpp
    ./gui/calendarform.cpp
    ./gui/searchparameters.cpp
    ./gui/formgrid.cpp
    ./gui/formgridsearch.cpp
    ./gui/mycombobox.cpp
    ./gui/formdocument.cpp
    ./gui/tableview.cpp
    ./gui/mynumericitemdelegate.cpp
    ./gui/mybooleanitemdelegate.cpp
    ./gui/docparameters.cpp
    ./gui/myitemdelegate.cpp
    ./gui/mylineitemdelegate.cpp
    ./gui/picture.cpp
    ./gui/mynumericedit.cpp
    ./gui/configform.cpp
    ./gui/wizardform.cpp
    ./gui/mybuttonlineedit.cpp
    ./gui/mybuttonlineedititemdelegate.cpp
    ./gui/wizarddictionary.cpp
    ./gui/wizardoperation.cpp
    ./gui/mytextedit.cpp
    ./gui/mysyntaxhighlighter.cpp
    ./gui/dialog.cpp
    ./gui/progressbar.cpp
    ./gui/mydateitemdelegate.cpp
    ./gui/mymdisubwindow.cpp
    ./gui/myprogressdialog.cpp
    ./gui/messagewindow.cpp

    ./engine/scriptengine.cpp
    ./engine/reportcontext.cpp
    ./engine/sqlqueryclass.cpp
    ./engine/sqlqueryprototype.cpp
    ./engine/sqlrecordclass.cpp
    ./engine/sqlrecordprototype.cpp
    ./engine/sqlfieldclass.cpp
    ./engine/sqlfieldprototype.cpp
    ./engine/eventloop.cpp
    ./engine/documentscriptengine.cpp

    ./report/reportengine.cpp
    ./report/reports.cpp
    ./report/ooreportengine.cpp
    ./report/ooxmlreportengine.cpp

    ./openoffice/ooxmlengine.cpp

    ./storage/dbfactory.cpp
    ./storage/mysqlrelationaltablemodel.cpp

    ./driverfr/driverfr.cpp

    ./serialport/qmyextserialport.cpp
    ./../qextserialport/src/qextserialport.cpp
    )

set ( PROJECT_NAME_HDRS

    ./kernel/app.h
    ./kernel/essence.h
    ./kernel/dictionary.h
    ./kernel/dictionaries.h
    ./kernel/documents.h
    ./kernel/document.h
    ./kernel/table.h
    ./kernel/saldo.h
    ./kernel/barcodereader.h
    ./kernel/tcpserver.h
    ./kernel/tcpclient.h

    ./gui/guifactory.h
    ./gui/passwordform.h
    ./gui/form.h
    ./gui/connectionform.h
    ./gui/mainwindow.h
    ./gui/calendarform.h
    ./gui/searchparameters.h
    ./gui/formgrid.h
    ./gui/mycombobox.h
    ./gui/formdocument.h
    ./gui/tableview.h
    ./gui/mynumericitemdelegate.h
    ./gui/mybooleanitemdelegate.h
    ./gui/docparameters.h
    ./gui/myitemdelegate.h
    ./gui/mylineitemdelegate.h
    ./gui/picture.h
    ./gui/mynumericedit.h
    ./gui/configform.h
    ./gui/wizardform.h
    ./gui/mybuttonlineedit.h
    ./gui/mybuttonlineedititemdelegate.h
    ./gui/wizarddictionary.h
    ./gui/wizardoperation.h
    ./gui/mytextedit.h
    ./gui/mysyntaxhighlighter.h
    ./gui/dialog.h
    ./gui/progressbar.h
    ./gui/mydateitemdelegate.h
    ./gui/mymdisubwindow.h
    ./gui/myprogressdialog.h
    ./gui/messagewindow.h

    ./engine/scriptengine.h
    ./engine/reportcontext.h
    ./engine/sqlqueryclass.h
    ./engine/sqlqueryprototype.h
    ./engine/sqlrecordclass.h
    ./engine/sqlrecordprototype.h
    ./engine/sqlfieldclass.h
    ./engine/sqlfieldprototype.h
    ./engine/eventloop.h

    ./report/reportengine.h
    ./report/ooreportengine.h
    ./report/ooxmlreportengine.h

    ./openoffice/ooxmlengine.h

    ./storage/dbfactory.h
    ./storage/mysqlrelationaltablemodel.h

    ./driverfr/driverfr.h

    ./serialport/qmyextserialport.h
    ./../qextserialport/src/qextserialport_p.h
    )
    
set ( PROJECT_NAME_RCS
       ../../resources.qrc
    )

if (${CMAKE_SYSTEM_NAME} STREQUAL Windows)
  set ( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -frtti -fexceptions -mthreads -Wall -Wl,--subsystem,console -mwindows -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_PLUGIN -DQT_THREAD_SUPPORT -DQDESIGNER_EXPORT_WIDGETS -DQT_NEEDS_QMAIN")
  if ( MINGW )
    # resource compilation for MinGW
    add_custom_command( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.o
                        COMMAND windres.exe -I${CMAKE_CURRENT_SOURCE_DIR} -i${CMAKE_CURRENT_SOURCE_DIR}/resources.rc 
                             -o ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.o )
    set ( PROJECT_NAME_SOURCES ${PROJECT_NAME_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.o)
	set ( CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> -enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc -Wl,-s -mthreads -Wl -Wl,-subsystem,console <OBJECTS>  -o <TARGET> -Wl,--major-image-version,<TARGET_VERSION_MAJOR>,--minor-image-version,<TARGET_VERSION_MINOR> -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32  -L${QT_LIBRARY_DIR} -lmingw32 -lqtmain -lQtScript4 -lQtSql4 -lQtNetwork4 -lQtUiTools -lQtDesigner4 -lQtXml4 -lQtGui4 -lQtCore4")
  else ( MINGW )
    set ( PROJECT_NAME_SOURCES ${PROJECT_NAME_SOURCES} resources.rc)
  endif ( MINGW )
else ()
endif ()

qt4_wrap_cpp ( PROJECT_NAME_MOC_HDRS ${PROJECT_NAME_HDRS} )

qt4_add_resources ( PROJECT_NAME_RCS_SRCS ${PROJECT_NAME_RCS} )     

add_executable ( ${PROJECT_NAME} WIN32 ${PROJECT_NAME_MOC_HDRS} ${PROJECT_NAME_SRCS} ${PROJECT_NAME_RCS_SRCS} ${PROJECT_NAME_SOURCES} )
target_link_libraries ( ${PROJECT_NAME} ${QT_LIBRARIES} )

