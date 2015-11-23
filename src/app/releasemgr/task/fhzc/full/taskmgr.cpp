#include <QLatin1String>

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

}//fullbuild
}//fhzc
}//task
}//releasemgr