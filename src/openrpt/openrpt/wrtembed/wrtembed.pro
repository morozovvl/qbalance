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

include( ../../global.pri )

TEMPLATE = lib
CONFIG += qt warn_on staticlib

INCLUDEPATH = ../../common ../common ../../../openrpt-build-desktop/common ../renderer ../images .

MOC_DIR     = tmp
UI_DIR      = tmp
OBJECTS_DIR = tmp
QT += xml sql
#VERSION = 0.1.0

CONFIG(debug){
    DESTDIR = ../../debug/lib
    LIBS += -L../../debug/lib -lDmtx_Library
} else {
    DESTDIR = ../../release/lib
    LIBS += -L../../release/lib -lDmtx_Library
}

#The following line was changed from FORMS to FORMS3 by qt3to4
FORMS   += labeleditor.ui \
           labeldefinitions.ui \
           labeldefinitioneditor.ui \
           queryeditor.ui \
           querylist.ui \
           pagesetup.ui \
           sectioneditor.ui \
           detailsectiondialog.ui \
           fieldeditor.ui \
           texteditor.ui \
           barcodeeditor.ui \
           reportproperties.ui \
           reportparameter.ui \
           reportparameterlist.ui \
           reportparameterlistitem.ui \
           imageeditor.ui \
           coloreditor.ui \
           colorlist.ui \
           grapheditor.ui \
           detailgroupsectiondialog.ui \
           editpreferences.ui \
           dbfiledialog.ui \
           crosstabeditor.ui \
           dmatrixsquareconfig.ui \
           dmatrixrectconfig.ui \
           dbarcodeconfig.ui \
           dmatrixpreview.ui \
           patheditor.ui

HEADERS += reportgridoptions.h\
           reporthandler.h \
           documentwindow.h \
           documentview.h \
           documentscene.h \
           graphicsitems.h \
           graphicssection.h \
           labeleditor.h \
           labeldefinitions.h \
           labeldefinitioneditor.h \
           queryeditor.h \
           querylist.h \
           pagesetup.h \
           sectioneditor.h \
           detailsectiondialog.h \
           fieldeditor.h \
           texteditor.h \
           barcodeeditor.h \
           reportproperties.h \
           reportparameter.h \
           reportparameterlist.h \
           reportparameterlistitem.h \
           imageeditor.h \
           coloreditor.h \
           colorlist.h \
           grapheditor.h \
           detailgroupsectiondialog.h \
           editpreferences.h \
           dbfiledialog.h \
           crosstabeditor.h \
           querycombobox.h \
           fontutils.h \
           ../common/labelsizeinfo.h \
           ../common/pagesizeinfo.h \
           ../common/builtinSqlFunctions.h \
           ../common/builtinformatfunctions.h \
           dmatrixsquareconfig.h \
           dmatrixrectconfig.h \
           dbarcodeconfig.h \
           dmatrixpreview.h \
           patheditor.h

SOURCES += reportgridoptions.cpp\
           reporthandler.cpp \
           documentwindow.cpp \
           documentview.cpp \
           documentscene.cpp \
           graphicsitems.cpp \
           graphicssection.cpp \
           labeldefinitions.cpp \
           labeldefinitioneditor.cpp \
           labeleditor.cpp \
           queryeditor.cpp \
           querylist.cpp \
           pagesetup.cpp \
           sectioneditor.cpp \
           detailsectiondialog.cpp \
           fieldeditor.cpp \
           texteditor.cpp \
           barcodeeditor.cpp \
           reportproperties.cpp \
           reportparameter.cpp \
           reportparameterlist.cpp \
           reportparameterlistitem.cpp \
           imageeditor.cpp \
           coloreditor.cpp \
           colorlist.cpp \
           grapheditor.cpp \
           detailgroupsectiondialog.cpp \
           editpreferences.cpp \
           dbfiledialog.cpp \
           crosstabeditor.cpp \
           querycombobox.cpp \
           fontutils.cpp \
           ../common/labelsizeinfo.cpp \
           ../common/pagesizeinfo.cpp \
           ../common/builtinSqlFunctions.cpp \
           ../common/builtinformatfunctions.cpp \
           dmatrixsquareconfig.cpp \
           dmatrixrectconfig.cpp \
           dbarcodeconfig.cpp \
           dmatrixpreview.cpp \
           patheditor.cpp

RESOURCES += ../images/OpenRPTWrtembed.qrc \
             ../images/OpenRPTCommon.qrc

TRANSLATIONS    = wrtembed_fr.ts wrtembed_it.ts wrtembed_ru.ts wrtembed_es.ts

INCLUDEPATH += ../Dmtx_Library
