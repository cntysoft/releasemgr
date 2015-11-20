#ifndef TASKMGR_H
#define TASKMGR_H

#include <QMap>
#include <QList>
#include <QString>
#include <QLatin1String>

#include "types.h"

namespace releasemgr 
{

class AbstractTask;
class Settings;

class AbstractTaskMgr
{
public:
   using TaskInitializerFnPtrType = AbstractTask* (*)(AbstractTaskMgr*);
   using TaskPoolType = QMap<QString, TaskInitializerFnPtrType>;
public:
   AbstractTaskMgr(const QLatin1String& moduleName, Settings& settings);
   const QLatin1String& getModuleName() const;
   Settings& getSysSettings();
   virtual ~AbstractTaskMgr();
protected:
   virtual void beforeRun() = 0;
   virtual void afterRun() = 0;
   virtual void beforeRunCycle(const AbstractTask& task) = 0;
   virtual void afterRunCycle(const AbstractTask& task) = 0;
protected:
   TaskPoolType taskInitializers;
private:
   QList<AbstractTask*> tasks;
   void initTaskRepo();
private:
   QLatin1String m_moduleName;
   Settings& m_settings;
};

}//releasemgr

#endif // TASKMGR_H
