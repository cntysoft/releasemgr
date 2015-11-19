#include "abstract_taskmgr.h"
#include "abstract_task.h"

namespace releasemgr 
{

AbstractTaskMgr::AbstractTaskMgr()
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

AbstractTaskMgr::~AbstractTaskMgr()
{
   while(!tasks.empty()){
      delete tasks.takeFirst();
   }
}

}//releasemgr