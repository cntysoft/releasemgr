#include <QScopedPointer>

#include "fhzc_build_command.h"
#include "task/fhzc/full/taskmgr.h"
#include "task/fhzc/diff/taskmgr.h"
#include "types.h"

namespace releasemgr{
namespace command{

FhzcBuildCommand::FhzcBuildCommand(CommandRunner& runner, const CommandMeta& invokeMeta)
   :AbstractCommand(runner, invokeMeta)
{}

void FhzcBuildCommand::exec()
{
   QScopedPointer<AbstractTaskMgr> taskmgr(getTaskMgr());
   taskmgr->run(m_invokeMeta.getCmdArgs());
   exit(EXIT_SUCCESS);
}

AbstractTaskMgr* FhzcBuildCommand::getTaskMgr()
{
   AbstractTaskMgr* taskmgr = nullptr;
   using FullBuildTaskMgr = releasemgr::task::fhzc::fullbuild::TaskMgr;
   using DiffBuildTaskMgr = releasemgr::task::fhzc::diffbuild::TaskMgr;
   TaskParamsType args = m_invokeMeta.getCmdArgs();
   QString action = args["action"];
   if("fullbuild" == action){
      taskmgr = new FullBuildTaskMgr(QLatin1String("Fhzc"), m_cmdRunner.getSysSettings());
   }else if("diffbuild" == action){
      taskmgr = new DiffBuildTaskMgr(QLatin1String("Fhzc"), m_cmdRunner.getSysSettings());
   }
   return taskmgr;
}

FhzcBuildCommand::~FhzcBuildCommand()
{}

}//command
}//releasemgr