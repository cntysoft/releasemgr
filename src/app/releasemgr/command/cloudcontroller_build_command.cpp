#include "cloudcontroller_build_command.h"

#include "task/cloudcontroller/rpm/taskmgr.h"

namespace releasemgr{
namespace command{

using sn::corelib::AbstractCommand;
using sn::corelib::CommandMeta;
using releasemgr::CommandRunner;

using CloudControllerRPMTaskMgr = task::cloudcontroller::rpmbuild::TaskMgr;

CloudControllerBuildCommand::CloudControllerBuildCommand(CommandRunner& runner, const CommandMeta &invokeMeta)
   :AbstractCommand(runner, invokeMeta)
{}

void CloudControllerBuildCommand::exec()
{
   //暂时就一种打包方式
   CloudControllerRPMTaskMgr cloudcontrollerRpmTaskMgr(QLatin1String("CloudController"), m_cmdRunner.getSysSettings());
   cloudcontrollerRpmTaskMgr.run(m_invokeMeta.getCmdArgs());
   exit(EXIT_SUCCESS);
}

CloudControllerBuildCommand::~CloudControllerBuildCommand()
{}


}//command
}//releasemgr
