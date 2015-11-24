#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QFileInfoList>

#include "io/filesystem.h"

namespace releasemgr 
{

bool Filesystem::traverseFs(const QString &path, int level, FsTraverFnType fn, FsTraverFlag flag)
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

void Filesystem::doTraverseFs(const QString &path, bool limitDepth, int level, int depth, FsTraverFnType fn, FsTraverFlag flag)
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