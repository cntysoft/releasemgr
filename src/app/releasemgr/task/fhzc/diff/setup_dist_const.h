#ifndef TASK_FHZC_DIFFBUILD_SETUP_DIST_CONST_H
#define TASK_FHZC_DIFFBUILD_SETUP_DIST_CONST_H

#include "diffbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhzc{
namespace diffbuild{

class SetupDistConst : public DiffBuildAbstractTask
{
public:
   SetupDistConst(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~SetupDistConst();
};

}//diffbuild
}//fhzc
}//task
}//releasemgr

#endif // TASK_FHZC_DIFFBUILD_SETUP_DIST_CONST_H
