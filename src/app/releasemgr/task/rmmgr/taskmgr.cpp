#include <QLatin1String>
#include <QDir>

#include "taskmgr.h"
#include "settings.h"

namespace releasemgr{
namespace task{
namespace rmmgr{
namespace fullbuild{

TaskMgr::TaskMgr(const QLatin1String& moduleName, Settings& settings)
   :AbstractTaskMgr(moduleName, settings)
{
}

void TaskMgr::beforeRun(const TaskParamsType& args)
{
   writeMsg("开始打包releasemgr系统, 打包版本为 : ");
   writeMsg(args[QLatin1String("version")].toString().toLatin1(), TerminalColor::LightBlue);
   writeMsg("\n-----------------------------------------------------------------------------------------\n");
}

void TaskMgr::afterRun(const TaskParamsType &args)
{
   QString buildDir = getSysSettings().getValue("buildDir", getModuleName()).toString();
   QString filename(buildDir+QDir::separator()+"releasemgr-"+args[QLatin1String("version")].toString()+".rpm\n");
   writeMsg(filename.toLatin1(), TerminalColor::Green);
}

}//fullbuild
}//rmmgr
}//task
}//releasemgr