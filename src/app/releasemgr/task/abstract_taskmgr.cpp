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
      TaskInitializerFnPtrType initializer = *iterator;
      m_tasks.append(initializer(*this, args));
      iterator++;
   }
}

void AbstractTaskMgr::run(const TaskParamsType& args)
{
   initTaskRepo(args);
   beforeRun(args);
   QList<AbstractTask*>::const_iterator it = m_tasks.cbegin();
   while(it != m_tasks.cend()){
      beforeRunCycle(*(*it));
      (*it)->exec();
      afterRunCycle(*(*it));
      it++;
   }
   afterRun(args);
}

const QLatin1String& AbstractTaskMgr::getModuleName() const
{
   return m_moduleName;
}

Settings& AbstractTaskMgr::getSysSettings() const
{
   return m_settings;
}

void AbstractTaskMgr::writeLine(const char *msg, TerminalColor color)
{
   Terminal::writeText(">> ", TerminalColor::Green);
   Terminal::writeText(msg, color);
   Terminal::writeText("\n");
}

void AbstractTaskMgr::writeMsg(const char *msg, TerminalColor color)
{
   Terminal::writeText(msg, color);
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
   while(!m_tasks.empty()){
      delete m_tasks.takeFirst();
   }
}

}//releasemgr