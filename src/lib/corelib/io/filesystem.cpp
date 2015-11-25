#include <QString>
#include <QFileInfo>
#include <QDir>

#include "io/filesystem.h"

namespace releasemgr 
{

QFileInfoList Filesystem::ls(const QString &path, int level)
{
   QDir targetDir(path);
   QFileInfoList ret;
   if(!targetDir.exists()){
      return ret;
   }
   if(1 == level){
      return targetDir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
   }
   Filesystem::traverseFs(path, level, [&ret](QFileInfo& fileInfo, int)->void{
      ret.append(fileInfo);
   });
   return ret;
}

}//releasemgr