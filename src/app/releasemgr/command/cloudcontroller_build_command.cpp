#include <QDebug>

#include "cloudcontroller_build_command.h"
#include "task/cloudcontroller/rpm/taskmgr.h"
#include "task/cloudcontroller/web/diff_build_task_mgr.h"
#include "task/cloudcontroller/web/full_build_task_mgr.h"

namespace releasemgr{
namespace command{

using sn::corelib::AbstractCommand;
using sn::corelib::CommandMeta;
using releasemgr::CommandRunner;

using CloudControllerRPMTaskMgr = task::cloudcontroller::rpmbuild::TaskMgr;
using CloudControllerWebFullBuildTaskMgr = task::cloudcontrollerweb::fullbuild::TaskMgr;
using CloudControllerWebDiffBuildTaskMgr = task::cloudcontrollerweb::diffbuild::TaskMgr;

CloudControllerBuildCommand::CloudControllerBuildCommand(CommandRunner& runner, const CommandMeta &invokeMeta)
   :AbstractCommand(runner, invokeMeta)
{}

void CloudControllerBuildCommand::exec()
{
   TaskParamsType args = m_invokeMeta.getCmdArgs();
   QString action = args["action"];
   if("webfullbuild" == action){
      CloudControllerWebFullBuildTaskMgr taskmgr(QLatin1String("CloudController"), m_cmdRunner.getSysSettings());
      taskmgr.run(m_invokeMeta.getCmdArgs());
   }else if("webdiffbuild" == action){
      CloudControllerWebDiffBuildTaskMgr taskmgr(QLatin1String("CloudController"), m_cmdRunner.getSysSettings());
      taskmgr.run(m_invokeMeta.getCmdArgs());
   }else if("rpmbuild" == action){
      CloudControllerRPMTaskMgr cloudcontrollerRpmTaskMgr(QLatin1String("CloudController"), m_cmdRunner.getSysSettings());
      cloudcontrollerRpmTaskMgr.run(m_invokeMeta.getCmdArgs());
   }
   exit(EXIT_SUCCESS);
}

CloudControllerBuildCommand::~CloudControllerBuildCommand()
{}


}//command
}//releasemgr
