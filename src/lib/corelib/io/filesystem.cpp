#include <QString>
#include <QFileInfo>
#include <QDir>

#include "io/filesystem.h"

namespace releasemgr 
{

bool Filesystem::traverseFs(const QString &path, int level, FsTraverFnType fn, FsTraverFlag flag)
{
   
   level--;
   if(level < -1){
      return false;
   }
   QFileInfo currentDir(path);
   if(!currentDir.exists()){
      return false;
   }
   if(!currentDir.isDir()){
      fn(currentDir);
      return true;
   }
   if(flag == FsTraverFlag::SelfFirst){
      fn(currentDir);
      
   }
}

}//releasemgr