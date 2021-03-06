#include <QScopedPointer>

#include "fhshop_build_command.h"
#include "task/fhshop/full/taskmgr.h"
#include "task/fhshop/diff/taskmgr.h"
#include "types.h"
#include "command_runner.h"
#include "command/command_meta.h"

namespace releasemgr{
namespace command{

FhshopBuildCommand::FhshopBuildCommand(CommandRunner& runner, const CommandMeta &invokeMeta)
   :AbstractCommand(runner, invokeMeta)
{}

void FhshopBuildCommand::exec()
{
   QScopedPointer<AbstractTaskMgr> taskmgr(getTaskMgr());
   taskmgr->run(m_invokeMeta.getCmdArgs());
   exit(EXIT_SUCCESS);
}

AbstractTaskMgr* FhshopBuildCommand::getTaskMgr()
{
   AbstractTaskMgr* taskmgr = nullptr;
   using FullBuildTaskMgr = releasemgr::task::fhshop::fullbuild::TaskMgr;
   using DiffBuildTaskMgr = releasemgr::task::fhshop::diffbuild::TaskMgr;
   TaskParamsType args = m_invokeMeta.getCmdArgs();
   QString action = args["action"];
   if("fullbuild" == action){
      taskmgr = new FullBuildTaskMgr(QLatin1String("Fhshop"), m_cmdRunner.getSysSettings());
   }else if("diffbuild" == action){
      taskmgr = new DiffBuildTaskMgr(QLatin1String("Fhshop"), m_cmdRunner.getSysSettings());
   }
   return taskmgr;
}

FhshopBuildCommand::~FhshopBuildCommand()
{}

}//command
}//releasemgr