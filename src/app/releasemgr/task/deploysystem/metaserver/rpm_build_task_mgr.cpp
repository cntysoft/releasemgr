#include <QLatin1String>
#include <QDir>
#include <QString>

#include "rpm_build_task_mgr.h"
#include "rpm_build_tasks.h"

#include "corelib/kernel/settings.h"
#include "corelib/io/terminal.h"

namespace releasemgr{
namespace task{
namespace deploysystem{
namespace metaserver{
namespace rpmbuild{

using sn::corelib::TerminalColor;
using sn::corelib::Settings;

TaskMgr::TaskMgr(const QLatin1String& moduleName, Settings& settings)
   :AbstractTaskMgr(moduleName, settings)
{
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new Clear(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new MakeProjectStructure(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new CopySourceFiles(taskmgr, args);
   });
   m_taskInitializers.append([](const AbstractTaskMgr& taskmgr, const TaskParamsType& args)-> AbstractTask*{
      return new BuildRpm(taskmgr, args);
   });
}

void TaskMgr::beforeRun(const TaskParamsType& args)
{
   writeMsg("开始打包meta server系统, 打包版本为 : ");
   writeMsg(args["version"].toLatin1(), TerminalColor::LightBlue);
   writeMsg("\n-----------------------------------------------------------------------------------------\n");
}

void TaskMgr::afterRun(const TaskParamsType &args)
{
   QString buildDir = getSysSettings().getValue("buildDir", getModuleName()).toString();
   QString filename(buildDir+QDir::separator()+"metaserver-"+args["version"]+"-1.x86_64.rpm\n");
   writeMsg(filename.toLatin1(), TerminalColor::Green);
}

}//rpmbuild
}//metaserver
}//deploysystem
}//task
}//releasemgr