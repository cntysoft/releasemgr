#include <QProcess>
#include <QStringList>
#include <QString>
#include <cstdlib>
#include <QFileInfo>
#include <QProcessEnvironment>
#include <cstdlib>

#include "build_rpm.h"
#include "task/abstract_taskmgr.h"
#include "kernel/errorinfo.h"
#include "io/filesystem.h"

namespace releasemgr{
namespace task{
namespace cloudcontroller{
namespace rpmbuild{

using sn::corelib::Filesystem;

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
   QString cmd = QString ("rpmbuild -bb --define=\"_topdir %1\" %2/cloudcontroller.spec").arg(m_buildDir, m_rpmSpecDir);
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
}//cloudcontroller
}//task
}//releasemgr

