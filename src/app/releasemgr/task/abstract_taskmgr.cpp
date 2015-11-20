#include "abstract_taskmgr.h"
#include "abstract_task.h"
#include "settings.h"

namespace releasemgr 
{

AbstractTaskMgr::AbstractTaskMgr(const QLatin1String& moduleName, Settings& settings)
   : m_moduleName(moduleName), m_settings(settings)
{
   initTaskRepo();
}

void AbstractTaskMgr::initTaskRepo()
{
   TaskPoolType::const_iterator iterator = taskInitializers.cbegin();
   while(iterator != taskInitializers.cend()){
      TaskInitializerFnPtrType initializer = iterator.value();
      tasks.append(initializer(this));
      iterator++;
   }
}

const QLatin1String& AbstractTaskMgr::getModuleName() const
{
   return m_moduleName;
}

Settings& AbstractTaskMgr::getSysSettings()
{
   return m_settings;
}

AbstractTaskMgr::~AbstractTaskMgr()
{
   while(!tasks.empty()){
      delete tasks.takeFirst();
   }
}

}//releasemgr