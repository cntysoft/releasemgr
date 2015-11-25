#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QFile>

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

bool Filesystem::copyFile(const QString &source, const QString &destination, bool overwrite)
{
   if(source == destination){
      return true;
   }
   QFile sourceFile(source);
   if(!sourceFile.exists()){
      return false;
   }
   QFileInfo destinationInfo(destination);
   QDir targetDir = destinationInfo.absoluteDir();
   if(!targetDir.exists()){
      targetDir.mkpath(".");
   }
   if(destinationInfo.exists() && overwrite){
      QFile::remove(destination);
   }
   if(!QFile::copy(source, destination)){
      return false;
   }
   return true;
}

}//releasemgr