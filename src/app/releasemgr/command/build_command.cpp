#include "build_command.h"
#include "task/cloudcontroller/rpm/taskmgr.h"
#include "task/cloudcontroller/web/diff_build_task_mgr.h"
#include "task/cloudcontroller/web/full_build_task_mgr.h"
#include "task/deploysystem/metaserver/rpm_build_task_mgr.h"
#include "task/deploysystem/luoxi/rpm_build_task_mgr.h"
#include "task/rmmgr/rpm_build_task_mgr.h"
#include "task/upgrademgr/master/rpm_build_task_mgr.h"
#include "task/upgrademgr/slave/rpm_build_task_mgr.h"
#include "task/zhuchao/web/full_build_task_mgr.h"

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

using ZhuChaoWebFullBuild = releasemgr::task::zhuchaoweb::fullbuild::TaskMgr;

ZhuChaoBuildCommand::ZhuChaoBuildCommand(CommandRunner& runner, const CommandMeta &invokeMeta)
   :AbstractCommand(runner, invokeMeta)
{}

void ZhuChaoBuildCommand::exec()
{
   TaskParamsType args = m_invokeMeta.getCmdArgs();
   QString action = args["action"];
   if("webfullbuild" == action){
      ZhuChaoWebFullBuild taskmgr(QLatin1String("ZhuChao"), m_cmdRunner.getSysSettings());
      taskmgr.run(m_invokeMeta.getCmdArgs());
   }
   exit(EXIT_SUCCESS);
}

ZhuChaoBuildCommand::~ZhuChaoBuildCommand()
{}

}//command
}//releasemgr
