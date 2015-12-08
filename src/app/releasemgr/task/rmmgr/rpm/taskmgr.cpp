#include <QLatin1String>
#include <QDir>

#include "taskmgr.h"
#include "settings.h"

#include "task/rmmgr/rpm/clear.h"
#include "task/rmmgr/rpm/make_project_structure.h"
#include "task/rmmgr/rpm/copy_source_files.h"

namespace releasemgr{
namespace task{
namespace rmmgr{
namespace rpmbuild{

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

}//rpmbuild
}//rmmgr
}//task
}//releasemgr
