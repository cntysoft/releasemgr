#include "deploysystem_build_command.h"

#include "upgrademgr_build_command.h"
#include "command/command_meta.h"
#include "command_runner.h"
#include "task/deploysystem/metaserver/rpm_build_task_mgr.h"
#include "task/deploysystem/luoxi/rpm_build_task_mgr.h"

namespace releasemgr{
namespace command{

using MetaServerTaskMgr = releasemgr::task::deploysystem::metaserver::rpmbuild::TaskMgr;
using LuoXiTaskMgr = releasemgr::task::deploysystem::luoxi::rpmbuild::TaskMgr;

DeploySystemBuildCommand::DeploySystemBuildCommand(CommandRunner& runner, const CommandMeta &invokeMeta)
   :AbstractCommand(runner, invokeMeta)
{}

void DeploySystemBuildCommand::exec()
{
   TaskParamsType args = m_invokeMeta.getCmdArgs();
   QString sysType = args["action"];
   
   if("metaserver" == sysType){
      MetaServerTaskMgr taskmgr(QLatin1String("MetaServer"), m_cmdRunner.getSysSettings());
      taskmgr.run(m_invokeMeta.getCmdArgs());
   }else if("luoxi" == sysType){
      LuoXiTaskMgr taskmgr(QLatin1String("LuoXi"), m_cmdRunner.getSysSettings());
      taskmgr.run(m_invokeMeta.getCmdArgs());
   }
   exit(EXIT_SUCCESS);
}

DeploySystemBuildCommand::~DeploySystemBuildCommand()
{}

}//command
}//releasemgr