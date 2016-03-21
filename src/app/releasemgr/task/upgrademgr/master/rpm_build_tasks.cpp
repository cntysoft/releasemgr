#include <QFileInfo>
#include <QProcessEnvironment>
#include <cstdlib>

#include "rpm_build_tasks.h"
#include "task/abstract_taskmgr.h"
#include "corelib/kernel/errorinfo.h"
#include "const.h"
#include "corelib/kernel/errorinfo.h"
#include "corelib/io/filesystem.h"
#include "corelib/global/common_funcs.h"

namespace releasemgr{
namespace task{
namespace upgrademgrmaster{
namespace rpmbuild{

using sn::corelib::ErrorInfo;
using sn::corelib::Filesystem;

RpmBuildAbstractTask::RpmBuildAbstractTask(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs)
   :AbstractTask(taskmgr, invokeArgs)
{
   if(m_invokeArgs.contains("projectdir")){
      m_projectDir = m_invokeArgs["projectdir"];
   }
   if(m_invokeArgs.contains("builddir")){
      m_buildDir = m_invokeArgs["builddir"];
   }
   if(!Filesystem::dirExist(m_projectDir)){
      throw ErrorInfo(QString("项目文件夹 %1 不存在").arg(m_projectDir));
   }
   //检查项目文件
   QString projectQbsFile(m_projectDir+"/upgrademgr_master.qbs");
   if(!Filesystem::fileExist(projectQbsFile)){
      throw ErrorInfo(QString("项目文件夹中项目文件%1不存在").arg("upgrademgr_master.qbs"));
   }
   m_rpmBuildDir = m_buildDir+DS+"BUILD";
   m_rpmRpmDir = m_buildDir+DS+"RPMS";
   m_rpmSourceDir = m_buildDir+DS+"SOURCES";
   m_rpmSpecDir = m_buildDir+DS+"SPECS";
   m_rpmSRpmDir = m_buildDir+DS+"SRPMS";
   m_rpmBuildRootDir = m_buildDir+DS+"BUILDROOT";
}

QString RpmBuildAbstractTask::getAssetDir()
{
   return AbstractTask::getAssetDir() + DS+"upgrademgr_master";
}

RpmBuildAbstractTask::~RpmBuildAbstractTask()
{}

Clear::Clear(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs)
   :RpmBuildAbstractTask(taskmgr, invokeArgs)
{}

void Clear::exec()
{
   writeBeginMsg("开始清除打包目录 ... ");
   if(Filesystem::fileExist(m_buildDir)){
      if(!Filesystem::isWritable(m_buildDir)){
         throw ErrorInfo("build directory is no writable");
      }
      Filesystem::deleteDirRecusive(m_buildDir);
   }
   Filesystem::createPath(m_buildDir);
   writeDoneMsg();
}

Clear::~Clear()
{}

MakeProjectStructure::MakeProjectStructure(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : RpmBuildAbstractTask(taskmgr, invokeArgs)
{}

void MakeProjectStructure::exec()
{
   writeBeginMsg("开始创建RPM打包文件目录结构 ... ");
   QStringList dirs{
      m_rpmBuildDir,
            m_rpmRpmDir,
            m_rpmSourceDir,
            m_rpmSpecDir,
            m_rpmSRpmDir,
            m_rpmBuildRootDir
   };
   QStringListIterator iterator(dirs);
   while (iterator.hasNext()) {
      Filesystem::createPath(iterator.next());
   }
   writeDoneMsg();
}

MakeProjectStructure::~MakeProjectStructure()
{}

CopySourceFiles::CopySourceFiles(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : RpmBuildAbstractTask(taskmgr, invokeArgs)
{}

void CopySourceFiles::exec()
{
   writeBeginMsg("正在复制upgrademgrmaster项目源码 ... ");
   QStringList filenames;
   Filesystem::traverseFs(m_projectDir, 0, [&filenames, this](QFileInfo& fileInfo, int)->void{
      QString ext = fileInfo.suffix();
      if(fileInfo.isFile() && (ext == "h" || ext == "cpp" || ext == "service" || ext == "qbs" || ext == "php" || ext == "tpl" || ext == "js")){
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
   if(!Filesystem::getOperateStatus()){
      throw ErrorInfo(Filesystem::getErrorString());
   }
   specFileContent.replace(QByteArray("<version>"), QByteArray(m_invokeArgs["version"].toLocal8Bit()));
   QString corelibVersion = sn::corelib::get_corelib_version();
   QStringList versionParts = corelibVersion.split('.');
   QString baseName = "/usr/local/lib/libsncore.so";
   QStringList paths{
      baseName
   };
   for(int i = 0; i < versionParts.size();i++){
      QString temp(baseName);
      for(int j = 0; j <= i; j++){
         temp += "."+versionParts[j];
      }
      paths << temp;
   }
   specFileContent.replace(QByteArray("<sncorepaths>"), QByteArray((paths.join('\n')).toLocal8Bit()));
   Filesystem::filePutContents(m_rpmSpecDir+DS+"upgrademgrmaster.spec", specFileContent);
   writeDoneMsg();
}

CopySourceFiles::~CopySourceFiles()
{}

BuildRpm::BuildRpm(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   :RpmBuildAbstractTask(taskmgr, invokeArgs)
{}

void BuildRpm::exec()
{
   writeBeginMsg("开始进行RPM打包 ... ");
   QProcessEnvironment env(QProcessEnvironment::systemEnvironment());
   QString ldLibraryPath(env.value("LD_LIBRARY_PATH"));
   ldLibraryPath = "/usr/lib64:"+ldLibraryPath;
   ::setenv("LD_LIBRARY_PATH", ldLibraryPath.toLocal8Bit(), 1);
   QString cmd = QString ("rpmbuild -bb --define=\"_topdir %1\" %2/upgrademgrmaster.spec").arg(m_buildDir, m_rpmSpecDir);
   std::system(cmd.toLocal8Bit());
   Filesystem::traverseFs(m_rpmRpmDir, 0, [this](QFileInfo fileInfo, int){
      if(fileInfo.isFile() && fileInfo.suffix() == "rpm"){
         QString source(fileInfo.absoluteFilePath());
         QString destination(source);
         destination.replace(fileInfo.absolutePath(), this->m_buildDir);
         Filesystem::copyFile(source, destination);
      }
      
   });
   writeDoneMsg();
}

BuildRpm::~BuildRpm()
{}

}//rpmbuild
}//upgrademgrmaster
}//task
}//releasemgr