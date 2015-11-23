#ifndef TASK_FHZC_FULLBUILD_CLEAR_H
#define TASK_FHZC_FULLBUILD_CLEAR_H

#include "task/abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

class Clear : public releasemgr::AbstractTask
{
public:
   Clear(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~Clear();
};

}//fullbuild
}//fhzc
}//task
}//releasemgr

#endif // TASK_FHZC_FULLBUILD_CLEAR_H
