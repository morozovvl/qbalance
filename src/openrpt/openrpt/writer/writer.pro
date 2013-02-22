#
# OpenRPT report writer and rendering engine
# Copyright (C) 2001-2012 by OpenMFG, LLC
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
# Please contact info@openmfg.com with any questions on this license.
#
QT += xml sql

include( ../../global.pri )

TEMPLATE = app
TARGET   = OpenRPT
unix:TARGET = openrpt

CONFIG += qt warn_on

MOC_DIR     = tmp
UI_DIR      = tmp
OBJECTS_DIR = tmp

INCLUDEPATH += ../../common ../common ../images

CONFIG(debug){
    PRE_TARGETDEPS += ../../debug/lib/libcommon.a       \
                      ../../debug/lib/libDmtx_Library.a \
                      ../../debug/lib/libwrtembed.a     \
                      ../../debug/lib/librenderer.a

    DESTDIR = ../../debug/bin
    LIBS += -L../../debug/lib -lwrtembed -lcommon -lrenderer -lDmtx_Library
} else {
    PRE_TARGETDEPS += ../../release/lib/libcommon.a       \
                      ../../release/lib/libDmtx_Library.a \
                      ../../release/lib/libwrtembed.a     \
                      ../../release/lib/librenderer.a

    DESTDIR = ../../release/bin
    LIBS += -L../../release/lib -lwrtembed -lcommon -lrenderer -lDmtx_Library
}

RC_FILE = writer.rc
macx:RC_FILE = ../images/OpenRPT.icns

HEADERS += reportwriterwindow.h \
           ../common/builtinSqlFunctions.h	# MANU

SOURCES += rptwrt.cpp\
           ../common/builtinSqlFunctions.cpp \	# MANU
           reportwriterwindow.cpp

RESOURCES += writer.qrc

TRANSLATIONS = writer_fr.ts writer_it.ts writer_ru.ts writer_es.ts
