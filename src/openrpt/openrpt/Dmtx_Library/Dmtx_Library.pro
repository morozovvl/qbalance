#-------------------------------------------------
#
# Project created by QtCreator 2011-11-04T09:42:59
#
#-------------------------------------------------

QT       -= gui

TARGET = Dmtx_Library
TEMPLATE = lib
CONFIG  += qt warn_on staticlib

DEFINES += DMTX_LIBRARY_LIBRARY

CONFIG(debug){
    DESTDIR = ../../debug/lib
} else {
    DESTDIR = ../../release/lib
}

SOURCES += \
    simple_test.c \
    dmtxvector2.c \
    dmtxtime.c \
    dmtxsymbol.c \
    dmtxscangrid.c \
    dmtxregion.c \
    dmtxreedsol.c \
    dmtxplacemod.c \
    dmtxmessage.c \
    dmtxmatrix3.c \
    dmtximage.c \
    dmtxencodestream.c \
    dmtxencodescheme.c \
    dmtxencodeoptimize.c \
    dmtxencodeedifact.c \
    dmtxencodec40textx12.c \
    dmtxencodebase256.c \
    dmtxencodeascii.c \
    dmtxencode.c \
    dmtxdecodescheme.c \
    dmtxdecode.c \
    dmtxbytelist.c \
    dmtx.c

HEADERS +=\
    dmtxstatic.h \
    dmtx.h \
    config.h
