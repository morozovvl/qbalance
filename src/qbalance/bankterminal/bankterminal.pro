CONFIG += plugin \
          core \
          script
          

unix:TARGET = ../../../plugins/bankterminal
win32:TARGET = ../../../../plugins/bankterminal

TEMPLATE = lib

DEPENDPATH += .
INCLUDEPATH += .

HEADERS += \
	    bankterminalplugin.h \
    bankterminal.h
SOURCES += \
	    bankterminalplugin.cpp \
    bankterminal.cpp



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



