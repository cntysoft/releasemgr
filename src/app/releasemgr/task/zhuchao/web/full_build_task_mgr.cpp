#include "full_build_task_mgr.h"
#include "task/zhuchao/web/full_build_tasks.h"
#include <QLatin1String>
#include <QDir>

namespace releasemgr{
namespace task{
namespace zhuchaoweb{
namespace fullbuild{

TaskMgr::TaskMgr(const QLatin1String& moduleName, Settings& settings)
   :AbstractTaskMgr(moduleName, settings)
{
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new Clear(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new CopyProjectFiles(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new GenerateVersionInfo(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new SetupDistConst(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new BuildJsProjects(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new DumpMysql(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new SetupConfig(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new Compress(taskmgr, args);
   });
}

void TaskMgr::beforeRun(const TaskParamsType& args)
{
   writeMsg("开始打包凤凰筑巢WEB系统, 打包版本为 : ");
   writeMsg(args["version"].toLatin1(), TerminalColor::LightBlue);
   writeMsg("\n-----------------------------------------------------------------------------------------\n");
}

void TaskMgr::afterRun(const TaskParamsType &args)
{
   QString buildDir = getSysSettings().getValue("buildDir", getModuleName()).toString();
   QString filename(buildDir+QDir::separator()+"zhuchaoweb_"+args["version"]+".tar.gz\n");
   writeMsg(filename.toLatin1(), TerminalColor::Green);
}

}//diffbuild
}//zhuchaoweb
}//task
}//releasemgr