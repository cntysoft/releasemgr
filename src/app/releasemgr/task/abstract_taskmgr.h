#ifndef TASKMGR_H
#define TASKMGR_H

#include "types.h"
#include <QMap>
#include <QList>
#include <QString>

namespace releasemgr 
{

class AbstractTask;

class AbstractTaskMgr
{
public:
   using TaskInitializerFnPtrType = AbstractTask* (*)(AbstractTaskMgr*);
   using TaskPoolType = QMap<QString, TaskInitializerFnPtrType>;
   AbstractTaskMgr();
   virtual ~AbstractTaskMgr();
protected:
   virtual void beforeRun() = 0;
   virtual void afterRun() = 0;
   virtual void beforeRunCycle(const AbstractTask& task) = 0;
   virtual void afterRunCycle(const AbstractTask& task) = 0;
   TaskPoolType taskInitializers;
private:
   QList<AbstractTask*> tasks;
   void initTaskRepo();
};

}//releasemgr

#endif // TASKMGR_H
