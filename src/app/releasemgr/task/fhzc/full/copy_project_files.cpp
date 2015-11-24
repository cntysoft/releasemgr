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
   Filesystem::traverseFs(m_projectDir, 1, [](QFileInfo& fileInfo, int)->void{
      qDebug() << fileInfo.absoluteFilePath();
   });
   //获取核心程序的文件集合
//   QDir kernelLibDir(m_projectDir+QDir.separator()+"Library");
   
}

CopyProjectFiles::~CopyProjectFiles()
{}

}//fullbuild
}//fhzc
}//task
}//releasemgr