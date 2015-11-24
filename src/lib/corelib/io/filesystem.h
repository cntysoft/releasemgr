#ifndef RMGR_CORE_IO_FILESYSTEM_H
#define RMGR_CORE_IO_FILESYSTEM_H

#include "global/global.h"

QT_BEGIN_INCLUDE_NAMESPACE
class QFileInfo;
class QString;
QT_END_NAMESPACE

namespace releasemgr 
{

class RMGR_EXPORT Filesystem
{
public:
   enum class FsTraverFlag{
      SelfFirst,
      ChildFirst
   };
   using FsTraverFnType = void (*)(QFileInfo& fileInfo, int depth);
public:
   static bool deleteDirRecusive(const QString& dir);
   static bool traverseFs(const QString& path, int level = 0, FsTraverFnType fn = nullptr, FsTraverFlag flag = FsTraverFlag::SelfFirst);
private:
   static void doTraverseFs(const QString& path, bool limitDepth = true, int level = 0, int depth = 0, FsTraverFnType fn = nullptr, FsTraverFlag flag = FsTraverFlag::SelfFirst);
};

}//releasemgr

#endif // RMGR_CORE_IO_FILESYSTEM_H
