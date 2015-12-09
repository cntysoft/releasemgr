#include <QProcess>
#include <QStringList>
#include <QString>
#include <cstdlib>
#include <QFileInfo>

#include "build_rpm.h"
#include "task/abstract_taskmgr.h"
#include "kernel/errorinfo.h"
#include "io/filesystem.h"

namespace releasemgr{
namespace task{
namespace rmmgr{
namespace rpmbuild{

BuildRpm::BuildRpm(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   :RpmBuildAbstractTask(taskmgr, invokeArgs)
{}

void BuildRpm::exec()
{
   writeBeginMsg("开始进行RPM打包 ... ");
   QString cmd = QString ("rpmbuild -bb --define=\"_topdir %1\" %2/releasemgr.spec").arg(m_buildDir, m_rpmSpecDir);
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
}//rmmgr
}//task
}//releasemgr

