#ifndef REPORT_GLOBAL_H
#define REPORT_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(REPORT_LIBRARY)
#  define REPORT_EXPORT Q_DECL_EXPORT
#else
#  define REPORT_EXPORT Q_DECL_IMPORT
#endif

#endif // REPORT_GLOBAL_H
