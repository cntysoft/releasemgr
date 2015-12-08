#include <QProcess>
#include <QStringList>

#include "build_rpm.h"
#include "task/abstract_taskmgr.h"
#include "kernel/errorinfo.h"

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
//   QProcess process;
//   QStringList args;
//   process.setWorkingDirectory(m_rpmBuildDir);
//   args << "app" << "build";
//   process.start("sencha", args);
//   bool status = process.waitForFinished(-1);
//   if(!status || process.exitCode() != 0){
//      throw ErrorInfo(process.errorString());
//   }
   writeDoneMsg();
}

BuildRpm::~BuildRpm()
{}

}//rpmbuild
}//rmmgr
}//task
}//releasemgr

