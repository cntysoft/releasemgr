#include "rmmgr_build_command.h"
#include "task/rmmgr/rpm/taskmgr.h"

#include <QDebug>
namespace releasemgr 
{
using RPMTaskMgr = releasemgr::task::rmmgr::rpmbuild::TaskMgr;
RmMgrBuildCommand::RmMgrBuildCommand(CommandRunner *runner, const CommandMeta &invokeMeta)
   :AbstractCommand(runner, invokeMeta)
{}

void RmMgrBuildCommand::exec()
{
   //暂时就一种打包方式
   RPMTaskMgr rpmTaskMgr(QLatin1String("RmMgr"), m_cmdRunner->getSysSettings());
   rpmTaskMgr.run(m_invokeMeta.getCmdArgs());
   exit(EXIT_SUCCESS);
}

RmMgrBuildCommand::~RmMgrBuildCommand()
{}

}//releasemgr