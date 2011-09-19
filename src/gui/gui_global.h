#ifndef GUI_GLOBAL_H
#define GUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GUI_LIBRARY)
#  define GUISHARED_EXPORT Q_DECL_EXPORT
#else
#  define GUISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GUI_GLOBAL_H
