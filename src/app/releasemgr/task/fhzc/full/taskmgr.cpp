#include <QLatin1String>

#include "taskmgr.h"
#include "settings.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

TaskMgr::TaskMgr(const QLatin1String& moduleName, Settings& settings)
   :AbstractTaskMgr(moduleName, settings)
{
//   m_taskInitializers.insert("clear", [](AbstractTaskMgr*, const TaskParamsType& args)-> AbstractTask*{
      
//   });
}

}//fullbuild
}//fhzc
}//task
}//releasemgr