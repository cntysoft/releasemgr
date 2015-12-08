#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QByteArray>

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

int Filesystem::filePutContents(const QString &filename, const QString &content)
{
   QFileInfo fileInfo(filename);
   QDir targetDir = fileInfo.absoluteDir();
   if(!fileInfo.exists()){
      targetDir.mkpath(".");
   }
   QFile target(filename);
   if(!target.open(QFile::WriteOnly| QFile::Truncate | QFile::Text)){
      return -1;
   }
   return target.write(content.toLocal8Bit());
}

QByteArray Filesystem::fileGetContents(const QString &filename)
{
   QFile target(filename);
   if(!target.exists() || !target.open(QFile::ReadOnly|QFile::Text)){
      return QByteArray();
   }
   return target.readAll();
}

bool Filesystem::deleteDirRecusive(const QString &dir)
{
   return QDir(dir).removeRecursively();
}

bool Filesystem::deleteDir(const QString &dir)
{
   return QDir(dir).remove(".");
}

bool Filesystem::createDir(const QString &dirName)
{
   return QDir(dirName).mkdir(".");
}

bool Filesystem::createPath(const QString &dirPath)
{
   return QDir(dirPath).mkpath(".");
}

bool Filesystem::isReadable(const QString &filename)
{
   return QFileInfo(filename).isReadable();
}

bool Filesystem::isWritable(const QString &filename)
{
   return QFileInfo(filename).isWritable();
}

bool Filesystem::fileExist(const QString &filePath)
{
   return QFileInfo(filePath).exists();
}

}//releasemgr