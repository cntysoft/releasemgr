#include <QLatin1String>
#include <QDir>

#include "taskmgr.h"

//#include "task/fhzc/diff/clear.h"
//#include "task/fhzc/diff/generate_diff_metainfo.h"
//#include "task/fhzc/diff/generate_versioninfo.h"
//#include "task/fhzc/diff/setup_dist_const.h"
//#include "task/fhzc/diff/analysis_database.h"
//#include "task/fhzc/diff/copy_upgrade_script.h"
//#include "task/fhzc/diff/compress.h"

namespace releasemgr{
namespace task{
namespace fhshop{
namespace diffbuild{

TaskMgr::TaskMgr(const QLatin1String& moduleName, Settings& settings)
   :AbstractTaskMgr(moduleName, settings)
{
//   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
//      return new Clear(taskmgr, args);
//   });
//   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
//      return new GenerateDiffMetaInfo(taskmgr, args);
//   });
//   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
//      return new GenerateVersionInfo(taskmgr, args);
//   });
//   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
//      return new SetupDistConst(taskmgr, args);
//   });
//   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
//      return new AnalysisDatabase(taskmgr, args);
//   });
//   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
//      return new CopyUpgradeScript(taskmgr, args);
//   });
//   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
//      return new Compress(taskmgr, args);
//   });
}

void TaskMgr::beforeRun(const TaskParamsType& args)
{
   writeMsg("开始差异性打包凤凰筑巢商家版系统, 打包范围为 : ");
   writeMsg(args["version"].toLatin1(), TerminalColor::LightBlue);
   writeMsg("\n-----------------------------------------------------------------------------------------\n");
}

void TaskMgr::afterRun(const TaskParamsType &args)
{
   QString buildDir = getSysSettings().getValue("buildDir", getModuleName()).toString();
   QString filename(buildDir+QDir::separator()+"fenghuangshop_patch_"+args["from"]+"_"+args["to"]+".gzip\n");
   writeMsg(filename.toLatin1(), TerminalColor::Green);
}

}//diffbuild
}//fhshop
}//task
}//releasemgr