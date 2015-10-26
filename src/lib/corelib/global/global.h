#ifndef GLOBAL_H
#define GLOBAL_H

#include <qglobal.h>
#ifdef RM_STATIC_LIB
   #define RM_EXPORT 
#else
   #ifdef RM_LIBRARY
      #define RM_EXPORT Q_DECL_EXPORT
   #else
      #define RM_EXPORT Q_DECL_IMPORT
   #endif
#endif

#endif // GLOBAL_H

