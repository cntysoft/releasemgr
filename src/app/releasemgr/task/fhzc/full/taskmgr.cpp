#include <QLatin1String>
#include <QDir>

#include "taskmgr.h"
#include "settings.h"

#include "task/fhzc/full/clear.h"
#include "task/fhzc/full/copy_project_files.h"
#include "task/fhzc/full/generate_versioninfo.h"
#include "task/fhzc/full/setup_dist_const.h"
#include "task/fhzc/full/build_js_projects.h"
#include "task/fhzc/full/dump_mysql.h"
#include "task/fhzc/full/setup_config.h"

namespace releasemgr{
namespace task{
namespace fhzc{
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
}

void TaskMgr::beforeRun(const TaskParamsType& args)
{
   writeMsg("开始打包凤凰筑巢系统, 打包版本为 : ");
   writeMsg(args[QLatin1String("version")].toString().toLatin1(), TerminalColor::LightBlue);
   writeMsg("\n-----------------------------------------------------------------------------------------\n");
}

void TaskMgr::afterRun(const TaskParamsType &args)
{
   QString buildDir = getSysSettings().getValue("buildDir", getModuleName()).toString();
   QString filename(buildDir+QDir::separator()+"fenghuang_"+args[QLatin1String("version")].toString()+".gzip\n");
   writeMsg(filename.toLatin1(), TerminalColor::Green);
}

}//fullbuild
}//fhzc
}//task
}//releasemgr