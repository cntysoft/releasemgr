#ifndef RELEASEMGR_TASK_ABSTRACT_TASKMGR_H
#define RELEASEMGR_TASK_ABSTRACT_TASKMGR_H

#include <QList>
#include <QString>
#include <QLatin1String>

#include "corelib/global/global.h"
#include "corelib/io/terminal.h"
#include "corelib/kernel/settings.h"

#include "types.h"

namespace releasemgr 
{

using sn::corelib::Terminal;
using sn::corelib::TerminalColor;
using sn::corelib::Settings;

class AbstractTask;

class SN_CORELIB_EXPORT AbstractTaskMgr
{
   Q_DISABLE_COPY(AbstractTaskMgr)
public:
   using TaskInitializerFnPtrType = AbstractTask* (*)(const AbstractTaskMgr& taskmgr, const TaskParamsType& args);
   using TaskPoolType = QList<TaskInitializerFnPtrType>;
public:
   AbstractTaskMgr(const QLatin1String& moduleName, Settings& settings);
   const QLatin1String& getModuleName() const;
   Settings& getSysSettings() const;
public:
   virtual void run(const TaskParamsType& args);
   virtual ~AbstractTaskMgr();
protected:
   void writeLine(const char* msg, TerminalColor color = TerminalColor::Default);
   void writeMsg(const char* msg, TerminalColor color = TerminalColor::Default);
protected:
   virtual void beforeRun(const TaskParamsType& args);
   virtual void afterRun(const TaskParamsType& args);
   virtual void beforeRunCycle(const AbstractTask& task);
   virtual void afterRunCycle(const AbstractTask& task);
protected:
   TaskPoolType m_taskInitializers;
private:
   void initTaskRepo(const TaskParamsType& args);
private:
   QList<AbstractTask*> m_tasks;
   QLatin1String m_moduleName;
   Settings& m_settings;
};

}//releasemgr

#endif // RELEASEMGR_TASK_ABSTRACT_TASKMGR_H
