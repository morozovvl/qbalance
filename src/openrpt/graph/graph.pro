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

include( ../global.pri )
QT +=  sql

TEMPLATE = app
CONFIG += qt warn_on
INCLUDEPATH += .

# Input
HEADERS += graph.h graphwindow.h
FORMS   += graphwindow.ui
SOURCES += graph.cpp graphwindow.cpp main.cpp

MOC_DIR = tmp
UI_DIR = tmp
OBJECTS_DIR = tmp


CONFIG(debug){
    DESTDIR = ../debug/bin
} else {
    DESTDIR = ../release/bin
}
