#include <QDebug>

#include "upgrademgr_build_command.h"
#include "command/command_meta.h"
#include "command_runner.h"

#include "task/upgrademgr/master/rpm/taskmgr.h"

namespace releasemgr{
namespace command{

using UpgrademgrMasterRPMTaskMgr = releasemgr::task::upgrademgrmaster::rpmbuild::TaskMgr;

UpgrademgrBuildCommand::UpgrademgrBuildCommand(CommandRunner& runner, const CommandMeta &invokeMeta)
   :AbstractCommand(runner, invokeMeta)
{}

void UpgrademgrBuildCommand::exec()
{
   //暂时就一种打包方式
   UpgrademgrMasterRPMTaskMgr upgrademgrMasterRpmTaskMgr(QLatin1String("UpgrademgrMaster"), m_cmdRunner.getSysSettings());
   upgrademgrMasterRpmTaskMgr.run(m_invokeMeta.getCmdArgs());
   exit(EXIT_SUCCESS);
}

UpgrademgrBuildCommand::~UpgrademgrBuildCommand()
{}

}//command
}//releasemgr