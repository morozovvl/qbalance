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
CONFIG += qt warn_on
INCLUDEPATH += ../common ../../common ../../../openrpt-build-desktop/common ../renderer

TARGET = RPTrender
unix:TARGET = rptrender

OBJECTS_DIR = tmp
MOC_DIR     = tmp
UI_DIR      = tmp

CONFIG(debug){
    PRE_TARGETDEPS += ../../debug/lib/libcommon.a       \
                      ../../debug/lib/librenderer.a

    DESTDIR = ../../debug/bin
    LIBS += -L../../debug/lib -lrenderer -lcommon -lDmtx_Library
} else {
    PRE_TARGETDEPS += ../../release/lib/libcommon.a       \
                      ../../release/lib/librenderer.a

    DESTDIR = ../../release/bin
    LIBS += -L../../release/lib -lrenderer -lcommon -lDmtx_Library
}

RC_FILE = renderapp.rc
macx:RC_FILE = ../images/OpenRPT.icns

# Input
FORMS   += renderwindow.ui \
           ../wrtembed/dbfiledialog.ui

HEADERS += ../common/builtinSqlFunctions.h \
           ../wrtembed/dbfiledialog.h \
           renderwindow.h

SOURCES += ../common/builtinSqlFunctions.cpp \
           ../wrtembed/dbfiledialog.cpp \
           renderwindow.cpp \
           main.cpp

RESOURCES += renderapp.qrc

TRANSLATIONS    = renderapp_fr.ts renderapp_it.ts renderapp_ru.ts renderapp_es.ts
