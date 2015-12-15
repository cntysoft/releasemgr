#include <QLatin1String>
#include <QDir>

#include "taskmgr.h"
#include "task/fhshop/full/clear.h"
#include "task/fhshop/full/copy_project_files.h"
#include "task/fhshop/full/build_js_projects.h"
#include "task/fhshop/full/dump_mysql.h"
#include "task/fhshop/full/generate_versioninfo.h"
#include "task/fhshop/full/setup_config.h"
#include "task/fhshop/full/setup_dist_const.h"
#include "task/fhshop/full/compress.h"

namespace releasemgr{
namespace task{
namespace fhshop{
namespace fullbuild{

void TaskMgr::beforeRun(const TaskParamsType& args)
{
   writeMsg("开始打包凤凰筑巢商家版系统, 打包版本为 : ");
   writeMsg(args["version"].toLatin1(), TerminalColor::LightBlue);
   writeMsg("\n-----------------------------------------------------------------------------------------\n");
}

TaskMgr::TaskMgr(const QLatin1String& moduleName, Settings& settings)
   :AbstractTaskMgr(moduleName, settings)
{
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new Clear(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new CopyProjectFiles(taskmgr, args);
   });
//   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
//      return new BuildJsProjects(taskmgr, args);
//   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new DumpMysql(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new GenerateVersionInfo(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new SetupConfig(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new SetupDistConst(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new Compress(taskmgr, args);
   });
}


void TaskMgr::afterRun(const TaskParamsType &args)
{
   QString buildDir = getSysSettings().getValue("buildDir", getModuleName()).toString();
   QString filename(buildDir+QDir::separator()+"fenghuangshop_"+args["version"]+".gzip\n");
   writeMsg(filename.toLatin1(), TerminalColor::Green);
}

}//fullbuild
}//fhshop
}//task
}//releasemgr