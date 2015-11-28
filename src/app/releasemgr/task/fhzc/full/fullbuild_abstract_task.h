#ifndef TASK_FHZC_FULLBUILD_FULLBUILD_ABSTRACT_TASK_H
#define TASK_FHZC_FULLBUILD_FULLBUILD_ABSTRACT_TASK_H

#include "task/abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

class FullBuildAbstractTask : public releasemgr::AbstractTask
{
public:
   FullBuildAbstractTask(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual ~FullBuildAbstractTask();
};

}//fullbuild
}//fhzc
}//task
}//releasemgr

#endif // TASK_FHZC_FULLBUILD_FULLBUILD_ABSTRACT_TASK_H
