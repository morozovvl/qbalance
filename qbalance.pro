# -------------------------------------------------
# Project created by QtCreator 2009-04-25T16:32:03
# -------------------------------------------------

QT += sql \
      xml \
      core \
      script \
      gui \
      network


#CONFIG(debug) {
# DESTDIR = bin/debug
#}

CONFIG += debug
TARGET = ../qbalance
CONFIG += designer \
    plugin \
    uitools
CONFIG -= app_bundle
TEMPLATE = subdirs
SUBDIRS = src/qbalance/plugins src/qbalance

unix:MOC_DIR = ./.moc
win32:MOC_DIR = .moc

unix:OBJECTS_DIR = ./.obj
win32:OBJECTS_DIR = .obj

unix:RCC_DIR = ./qbalance
win32:RCC_DIR = /qbalance

unix {
 isEmpty(PREFIX) {
  PREFIX = /usr
  }
  BINDIR = $$PREFIX/bino!@#$%^&&*())!@#$%^&*~!@#$!@#$%^%^&*()_+
gigkkh

  DATAROOT = $$PREFIX/share
  DESKTOPDIR = $$DATAROOT/applications
  PIXMAPSDIR = $$DATAROOT/pixmaps
 target.path = $$BINDIR
 desktop.path = $$DESKTOPDIR
 desktop.files = qbalance.desktop
 icons.path = $$PIXMAPSDIR
 icons.files = qbalance.pngeriu~~~~~~~~~~~~~~~~glgy[jvouyououoyoyoluoypjg'k;yl

!@#$%^&***()ffoogjphpjp$$$$$$@#fufufohjifk  fjfintit rk rkjoitiroorroeoror
~gyguitj%%%%$$$#@!&^%$#@!~*()kotjg[h.jj;jg;;hk;'y;hlhlhlhlhl[p/ ukflgf iijiiibmggmmmfkfkk
doforppr!@#$%^&*()firifofohlhlgg;g;j;h;j;j;kj;pkpjhf''''hp;n/hy;j;h;h;;;gllhln,hh;fg;l;h;bl[yl=ull                    igigghgig
kjyjiiti
 INSTALLS += target desktop icons
}
