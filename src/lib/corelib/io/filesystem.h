#ifndef RMGR_CORE_IO_FILESYSTEM_H
#define RMGR_CORE_IO_FILESYSTEM_H

#include <QFileInfoList>
#include <QDir>

#include "global/global.h"

QT_BEGIN_INCLUDE_NAMESPACE
class QFileInfo;
class QString;
class QByteArray;
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
public:
   static bool deleteDirRecusive(const QString& dir);
   static bool deleteDir(const QString& dir);
   static QFileInfoList ls(const QString& path, int level = 1);
   template <typename FnType>
   static bool traverseFs(const QString& path, int level = 0, FnType fn = nullptr, FsTraverFlag flag = FsTraverFlag::SelfFirst);
   static bool copyFile(const QString& source, const QString& destination, bool overwrite = false);
   static QByteArray fileGetContents(const QString& filename);
   static int filePutContents(const QString& filename, const QString& content);
private:
   template <typename FnType>
   static void doTraverseFs(const QString& path, bool limitDepth = true, int level = 0, int depth = 0, FnType fn = nullptr, FsTraverFlag flag = FsTraverFlag::SelfFirst);
};

template <typename FnType>
bool Filesystem::traverseFs(const QString &path, int level, FnType fn, FsTraverFlag flag)
{
   bool limit = true;
   if(level == 0){
      limit = false;
   }
   QFileInfo currentDir(path);
   if(!currentDir.exists()){
      return false;
   }
   doTraverseFs(path, limit, level, 0, fn, flag);
   return true;
}

template <typename FnType>
void Filesystem::doTraverseFs(const QString &path, bool limitDepth, int level, int depth, FnType fn, FsTraverFlag flag)
{
   if(limitDepth && depth > level){
      return;
   }
   QFileInfo self(path);
   if(self.isFile()){
      fn(self, depth);
      return;
   }
   QDir selfDir(path);
   QDir::Filters filter(QDir::AllEntries | QDir::NoDotAndDotDot);
   selfDir.setFilter(filter);
   QFileInfoList children = selfDir.entryInfoList();
   ++depth;
   if(FsTraverFlag::SelfFirst == flag){
      if(depth > 1){
         fn(self, depth);
      }
      QFileInfoList::const_iterator it = children.cbegin();
      while(it != children.cend()){
         doTraverseFs((*it).absoluteFilePath(), limitDepth, level, depth, fn, flag);
         it++;
      }
   }else if(FsTraverFlag::ChildFirst == flag){
      QFileInfoList::const_iterator it = children.cbegin();
      while(it != children.cend()){
         doTraverseFs((*it).absoluteFilePath(), limitDepth, level, depth, fn, flag);
         it++;
      }
      if(depth > 1){
         fn(self, depth);
      }
   }
}

}//releasemgr

#endif // RMGR_CORE_IO_FILESYSTEM_H
