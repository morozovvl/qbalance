#ifndef OdfPreviewLib_GLOBAL_H
#define OdfPreviewLib_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(OdfPreviewLib_LIBRARY)
#  define OdfPreviewLibSHARED_EXPORT Q_DECL_EXPORT
#else
#  define OdfPreviewLibSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // OdfPreviewLib_GLOBAL_H
