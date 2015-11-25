#include <QDir>
#include <QStringList>
#include <QFileInfo>
#include <QDebug>

#include "copy_project_files.h"
#include "task/abstract_taskmgr.h"
#include "kernel/errorinfo.h"
#include "io/filesystem.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

CopyProjectFiles::CopyProjectFiles(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs)
   :AbstractTask(taskmgr, invokeArgs)
{}

void CopyProjectFiles::exec()
{
   writeBeginMsg("复制项目PHP部分文件夹 ... ");
   QDir buildDir(m_buildDir);
   if(!buildDir.exists()){
      buildDir.mkpath(".");
   }
   QStringList filenames;
   QChar ds = QDir::separator();
   //获取核心程序的文件集合
   Filesystem::traverseFs(m_projectDir+ds+"Library", 0, [&filenames](QFileInfo& fileInfo, int)->void{
      QString filename = fileInfo.absoluteFilePath();
      if(fileInfo.isFile() && !filename.contains("ReleaseTools")){
         filenames.append(filename);
      }
   });
   //获取指定的文件夹的文件集合
   QStringList specifyDirs{
            m_projectDir+ds+"Modules",
            m_projectDir+ds+"Apps",
            m_projectDir+ds+"Config",
            m_projectDir+ds+"SysApiHandler",
            m_projectDir+ds+"JsLibraray",
            m_projectDir+ds+"Data"+ds+"Framework",
            m_projectDir+ds+"Statics",
            m_projectDir+ds+"TagLibrary"
   };
   QStringList::const_iterator it = specifyDirs.cbegin();
   while(it != specifyDirs.cend()){
      Filesystem::traverseFs(*it, 0, [&filenames](QFileInfo& fileInfo, int)->void{
         if(fileInfo.isFile()){
            filenames.append(fileInfo.absoluteFilePath());
         }
      });
      it++;
   }
   collectSpecialFilenames(filenames);
   it = filenames.cbegin();
   while(it != filenames.cend()){
      QString sourceFilename(*it);
      QString destinationFilename(sourceFilename);
      destinationFilename.replace(m_projectDir, m_buildDir);
      Filesystem::copyFile(sourceFilename, destinationFilename);
      it++;
   }
   writeDoneMsg();
}

void CopyProjectFiles::collectSpecialFilenames(QStringList& filenames)
{
   QChar ds = QDir::separator();
   filenames.append(m_projectDir+ds+"index.php");
}

CopyProjectFiles::~CopyProjectFiles()
{}

}//fullbuild
}//fhzc
}//task
}//releasemgr