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
#The following line was inserted by qt3to4
QT += xml sql

include( ../../global.pri )

TEMPLATE = app
CONFIG += qt warn_on
INCLUDEPATH += ../common ../../common ../../../openrpt-build-desktop/common .

TARGET=importrptgui

OBJECTS_DIR = tmp
MOC_DIR     = tmp
UI_DIR      = tmp

CONFIG(debug){
    PRE_TARGETDEPS += ../../debug/lib/libcommon.a
    DESTDIR = ../../debug/bin
    LIBS += -L../../debug/lib -lcommon
} else {
    PRE_TARGETDEPS += ../../release/lib/libcommon.a
    DESTDIR = ../../release/bin
    LIBS += -L../../release/lib -lcommon
}

# Input
FORMS   += importwindow.ui

HEADERS += importwindow.h \
           ../common/builtinSqlFunctions.h

SOURCES += importwindow.cpp \
           ../common/builtinSqlFunctions.cpp \
           main.cpp
