#ifndef TASK_FHSHOP_FULLBUILD_FULLBUILD_ABSTRACT_TASK_H
#define TASK_FHSHOP_FULLBUILD_FULLBUILD_ABSTRACT_TASK_H

#include "task/abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhshop{
namespace fullbuild{

class FullBuildAbstractTask : public releasemgr::AbstractTask
{
public:
   FullBuildAbstractTask(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual ~FullBuildAbstractTask();
};

}//fullbuild
}//fhshop
}//task
}//releasemgr

#endif // TASK_FHSHOP_FULLBUILD_FULLBUILD_ABSTRACT_TASK_H
