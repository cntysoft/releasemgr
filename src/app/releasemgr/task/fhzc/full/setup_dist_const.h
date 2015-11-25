#ifndef TASK_FHZC_FULLBUILD_SETUP_DIST_CONST_H
#define TASK_FHZC_FULLBUILD_SETUP_DIST_CONST_H

#include "task/abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

class SetupDistConst : public releasemgr::AbstractTask
{
public:
   SetupDistConst(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~SetupDistConst();
};

}//fullbuild
}//fhzc
}//task
}//releasemgr

#endif // TASK_FHZC_FULLBUILD_SETUP_DIST_CONST_H
