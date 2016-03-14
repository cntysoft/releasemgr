#include "upgrademgr_build_command.h"
#include "command/command_meta.h"
#include "command_runner.h"

#include "task/upgrademgr/master/rpm_build_task_mgr.h"
#include "task/upgrademgr/slave/rpm_build_task_mgr.h"

namespace releasemgr{
namespace command{

using UpgrademgrMasterRPMTaskMgr = releasemgr::task::upgrademgrmaster::rpmbuild::TaskMgr;
using UpgrademgrSlaveRPMTaskMgr = releasemgr::task::upgrademgrslave::rpmbuild::TaskMgr;

UpgrademgrBuildCommand::UpgrademgrBuildCommand(CommandRunner& runner, const CommandMeta &invokeMeta)
   :AbstractCommand(runner, invokeMeta)
{}

void UpgrademgrBuildCommand::exec()
{
   TaskParamsType args = m_invokeMeta.getCmdArgs();
   QString sysType = args["subsystem"];
   if("master" == sysType){
      UpgrademgrMasterRPMTaskMgr taskmgr(QLatin1String("UpgrademgrMaster"), m_cmdRunner.getSysSettings());
      taskmgr.run(m_invokeMeta.getCmdArgs());
   }else if("slave" == sysType){
      UpgrademgrSlaveRPMTaskMgr taskmgr(QLatin1String("UpgrademgrSlave"), m_cmdRunner.getSysSettings());
      taskmgr.run(m_invokeMeta.getCmdArgs());
   }
   exit(EXIT_SUCCESS);
}

UpgrademgrBuildCommand::~UpgrademgrBuildCommand()
{}

}//command
}//releasemgr