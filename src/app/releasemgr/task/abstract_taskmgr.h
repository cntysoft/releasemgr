#ifndef ABSTRACT_TASKMGR_H
#define ABSTRACT_TASKMGR_H

#include <QMap>
#include <QList>
#include <QString>
#include <QLatin1String>

#include "global/global.h"
#include "types.h"

namespace releasemgr 
{

class AbstractTask;
class Settings;

class RMGR_EXPORT AbstractTaskMgr
{
   Q_DISABLE_COPY(AbstractTaskMgr)
public:
   using TaskInitializerFnPtrType = AbstractTask* (*)(AbstractTaskMgr*, const TaskParamsType& args);
   using TaskPoolType = QMap<QString, TaskInitializerFnPtrType>;
public:
   AbstractTaskMgr(const QLatin1String& moduleName, Settings& settings);
   const QLatin1String& getModuleName() const;
   Settings& getSysSettings() const;
public:
   virtual void run(const TaskParamsType& args);
   virtual ~AbstractTaskMgr();
protected:
   virtual void beforeRun(const TaskParamsType& args);
   virtual void afterRun(const TaskParamsType& args);
   virtual void beforeRunCycle(const AbstractTask& task);
   virtual void afterRunCycle(const AbstractTask& task);
protected:
   TaskPoolType m_taskInitializers;
private:
   QList<AbstractTask*> tasks;
   void initTaskRepo(const TaskParamsType& args);
private:
   QLatin1String m_moduleName;
   Settings& m_settings;
};

}//releasemgr

#endif // ABSTRACT_TASKMGR_H
