#include "abstract_taskmgr.h"
#include "abstract_task.h"
#include "settings.h"

namespace releasemgr 
{

AbstractTaskMgr::AbstractTaskMgr(const QLatin1String& moduleName, Settings& settings)
   : m_moduleName(moduleName), m_settings(settings)
{
}

void AbstractTaskMgr::initTaskRepo(const TaskParamsType& args)
{
   TaskPoolType::const_iterator iterator = m_taskInitializers.cbegin();
   while(iterator != m_taskInitializers.cend()){
      TaskInitializerFnPtrType initializer = iterator.value();
      tasks.append(initializer(this, args));
      iterator++;
   }
}

void AbstractTaskMgr::run(const TaskParamsType& args)
{
   initTaskRepo(args);
}

const QLatin1String& AbstractTaskMgr::getModuleName() const
{
   return m_moduleName;
}

Settings& AbstractTaskMgr::getSysSettings() const
{
   return m_settings;
}

void AbstractTaskMgr::beforeRun(const TaskParamsType&)
{}

void AbstractTaskMgr::afterRun(const TaskParamsType&)
{}

void AbstractTaskMgr::beforeRunCycle(const AbstractTask&)
{}

void AbstractTaskMgr::afterRunCycle(const AbstractTask&)
{}

AbstractTaskMgr::~AbstractTaskMgr()
{
   while(!tasks.empty()){
      delete tasks.takeFirst();
   }
}

}//releasemgr