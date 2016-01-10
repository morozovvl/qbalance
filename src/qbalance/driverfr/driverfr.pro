CONFIG += plugin

unix:TARGET = ../../../plugins/driverfr
win32:TARGET = ../../../../plugins/driverfr

TEMPLATE = lib

DEPENDPATH += .
INCLUDEPATH += .

HEADERS += driverfr.h \
            driverfrplugin.h
SOURCES += driverfr.cpp \
            driverfrplugin.cpp

unix:MOC_DIR = ../../../.moc
win32:MOC_DIR = ../../../.moc

unix:OBJECTS_DIR = ../../../.obj
win32:OBJECTS_DIR = ../../../.obj

unix:RCC_DIR = ../..
win32:RCC_DIR = ../..

unix {
 isEmpty(PREFIX) {
  PREFIX =   /usr
  }
  BINDIR =   $$PREFIX/bin
  DATAROOT =   $$PREFIX/share
  DESKTOPDIR =   $$DATAROOT/applications
  PIXMAPSDIR =   $$DATAROOT/pixmaps
 target.path =  $$BINDIR
 desktop.path =  $$DESKTOPDIR
 desktop.files =  qbalance.desktop
 icons.path =  $$PIXMAPSDIR
 icons.files =  qbalance.png
 INSTALLS +=  target  desktop  icons
}



