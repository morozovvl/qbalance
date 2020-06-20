# -------------------------------------------------
# Project created by QtCreator 2009-04-25T16:32:03
# -------------------------------------------------

#QMAKE_CXXFLAGS += -Wl,--rpath='$ORIGIN'/lib64/glibc
#QMAKE_CXXFLAGS += -Wl,--dynamic-linker='$ORIGIN'/lib64/ld-linux-x86-64.so.2
   
TEMPLATE = subdirs
SUBDIRS = src/qbalance/plugins \
          src/qbalance/bankterminal \
          src/qbalance/barcodereader \
          src/qbalance/cardcodereader \
          src/qbalance/driverfr \
          src/qbalance/gsmmodem \
          src/qbalance/emailclient \
          src/qbalance

#          src/gsl \

