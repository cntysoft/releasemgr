#ifndef RMGR_CORE_IO_FILESYSTEM_H
#define RMGR_CORE_IO_FILESYSTEM_H

#include "global/global.h"

QT_BEGIN_INCLUDE_NAMESPACE
class QFileInfo;
class QString;
QT_END_NAMESPACE

namespace releasemgr 
{

class Filesystem
{
public:
   enum class FsTraverFlag{
      SelfFirst,
      ChildFirst
   };
   using FsTraverFnType = void (*)(QFileInfo& fileInfo, int depth);
public:
   static bool deleteDirRecusive(const QString& dir);
   static bool traverseFs(const QString& path, int level = 1, FsTraverFnType fn = nullptr, FsTraverFlag flag = FsTraverFlag::SelfFirst);
};

}//releasemgr

#endif // RMGR_CORE_IO_FILESYSTEM_H
