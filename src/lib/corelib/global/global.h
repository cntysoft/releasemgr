#ifndef RMGR_CORE_GLOBAL_H
#define RMGR_CORE_GLOBAL_H

#include <qglobal.h>
#ifdef RMGR_STATIC_LIB
   #define RMGR_EXPORT 
#else
   #ifdef RMGR_LIBRARY
      #define RMGR_EXPORT Q_DECL_EXPORT
   #else
      #define RMGR_EXPORT Q_DECL_IMPORT
   #endif
#endif

#endif // RMGR_CORE_GLOBAL_H