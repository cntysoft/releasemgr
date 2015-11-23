#include <QLatin1String>
#include <QDir>

#include "taskmgr.h"
#include "settings.h"

#include "task/fhzc/full/clear.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

TaskMgr::TaskMgr(const QLatin1String& moduleName, Settings& settings)
   :AbstractTaskMgr(moduleName, settings)
{
   m_taskInitializers.insert("clear", [](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new Clear(taskmgr, args);
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