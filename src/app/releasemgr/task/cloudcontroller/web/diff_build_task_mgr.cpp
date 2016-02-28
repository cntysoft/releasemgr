#include "diff_build_task_mgr.h"
#include "task/cloudcontroller/web/diff_build_tasks.h"

#include <QLatin1String>
#include <QDir>

namespace releasemgr{
namespace task{
namespace cloudcontrollerweb{
namespace diffbuild{

TaskMgr::TaskMgr(const QLatin1String& moduleName, Settings& settings)
   :AbstractTaskMgr(moduleName, settings)
{
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new Clear(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new GenerateDiffMetaInfo(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new GenerateVersionInfo(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new SetupDistConst(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new AnalysisDatabase(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new CopyUpgradeScript(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new Compress(taskmgr, args);
   });
}

void TaskMgr::beforeRun(const TaskParamsType& args)
{
   writeMsg("开始差异性打包云管理WEB平台系统, 打包范围为 : ");
   writeMsg(QString("%1 -> %2").arg(args["from"]).arg(args["to"]).toLocal8Bit(), TerminalColor::LightBlue);
   writeMsg("\n-----------------------------------------------------------------------------------------\n");
}

void TaskMgr::afterRun(const TaskParamsType &args)
{
   QString buildDir = getSysSettings().getValue("webBuildDir", getModuleName()).toString();
   QString filename(buildDir+QDir::separator()+"cloudcontrollerweb_patch_"+args["from"]+"_"+args["to"]+".tar.gz\n");
   writeMsg(filename.toLatin1(), TerminalColor::Green);
}


}//diffbuild
}//cloudcontrollerweb
}//task
}//releasemgr