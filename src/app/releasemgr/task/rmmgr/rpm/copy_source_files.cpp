#include <QStringList>
#include <QFileInfo>
#include <QByteArray>
#include <QDebug>

#include "copy_source_files.h"
#include "task/abstract_taskmgr.h"
#include "io/filesystem.h"
#include "const.h"

namespace releasemgr{
namespace task{
namespace rmmgr{
namespace rpmbuild{

CopySourceFiles::CopySourceFiles(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : RpmBuildAbstractTask(taskmgr, invokeArgs)
{}

void CopySourceFiles::exec()
{
   writeBeginMsg("正在复制ReleaseMgr项目源码 ... ");
   QStringList filenames;
   Filesystem::traverseFs(m_projectDir, 0, [&filenames, this](QFileInfo& fileInfo, int)->void{
      QString ext = fileInfo.suffix();
      if(fileInfo.isFile() && (ext == "h" || ext == "cpp" || ext == "qbs" || ext == "php" || ext == "tpl" || ext == "js")){
         QString source = fileInfo.absoluteFilePath();
         QString destination(source);
         destination.replace(this->m_projectDir, this->m_rpmSourceDir);
         Filesystem::copyFile(source, destination);
      }
   });
   writeDoneMsg();
   processSpecFile();
   
}

void CopySourceFiles::processSpecFile()
{
   writeBeginMsg("正在处理Spec文件 ... ");
   QByteArray specFileContent(Filesystem::fileGetContents(getAssetDir()+DS+"rpmspec.tpl"));
   specFileContent.replace(QByteArray("<version>"), QByteArray(m_invokeArgs[QLatin1String("version")].toString().toLocal8Bit()));
   Filesystem::filePutContents(m_rpmSpecDir+DS+"releasemgr.spec", specFileContent);
   writeDoneMsg();
}

CopySourceFiles::~CopySourceFiles()
{}

}//rpmbuild
}//rmmgr
}//task
}//releasemgr