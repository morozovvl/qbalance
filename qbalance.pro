# -------------------------------------------------
# Project created by QtCreator 2009-04-25T16:32:03
# -------------------------------------------------

TEMPLATE = subdirs
SUBDIRS = src/qextserialport \
	  src/qbalance/plugins \
          src/qbalance
          

# build must be last:
CONFIG += release
#SUBDIRS += build

#windows {
#    CONFIG += rtti
#}

