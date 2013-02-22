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

#include( ../../global.pri )

QT += xml sql

TEMPLATE     = lib
CONFIG      += qt warn_on
INCLUDEPATH += ../common    \
               ../../common \
               ../renderer

DEFINES += REPORT_LIBRARY

TARGET      = report

OBJECTS_DIR = tmp
MOC_DIR     = tmp
UI_DIR      = tmp

CONFIG(debug){
    PRE_TARGETDEPS += ../../debug/lib/libcommon.a   \
                      ../../debug/lib/librenderer.a

    LIBS += -L../../debug/lib -lrenderer -lcommon -lDmtx_Library
    DESTDIR = ../../debug/dll
} else {
    PRE_TARGETDEPS += ../../release/lib/libcommon.a   \
                      ../../release/lib/librenderer.a

    DESTDIR = ../../release/lib
    LIBS += -L../../release/lib -lrenderer -lcommon -lDmtx_Library
}

win32 {
    CONFIG += dll
}

HEADERS += report.h \
           wrapper.h \
           report_global.h \
           modelwrapper.h \
    templategenerator.h

SOURCES += report.cpp \
           wrapper.cpp\
           modelwrapper.cpp \
    templategenerator.cpp

RESOURCES += report.qrc
