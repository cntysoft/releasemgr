#include "rmmgr_build_command.h"
#include "task/rmmgr/rpm_build_task_mgr.h"
#include "command/command_meta.h"
#include "command_runner.h"

namespace releasemgr{
namespace command{

using ReleaseMgrRPMTaskMgr = releasemgr::task::rmmgr::rpmbuild::TaskMgr;

RmMgrBuildCommand::RmMgrBuildCommand(CommandRunner& runner, const CommandMeta &invokeMeta)
   :AbstractCommand(runner, invokeMeta)
{}

void RmMgrBuildCommand::exec()
{
   //暂时就一种打包方式
   ReleaseMgrRPMTaskMgr rpmTaskMgr(QLatin1String("RmMgr"), m_cmdRunner.getSysSettings());
   rpmTaskMgr.run(m_invokeMeta.getCmdArgs());
   exit(EXIT_SUCCESS);
}

RmMgrBuildCommand::~RmMgrBuildCommand()
{}

}//command
}//releasemgr