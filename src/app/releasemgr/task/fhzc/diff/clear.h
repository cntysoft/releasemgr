#ifndef RELEASEMGR_TASK_FHZC_DIFFBUILD_CLEAR_H
#define RELEASEMGR_TASK_FHZC_DIFFBUILD_CLEAR_H

#include "diffbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhzc{
namespace diffbuild{

class Clear : public DiffBuildAbstractTask
{
public:
   Clear(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~Clear();
};

}//diffbuild
}//fhzc
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_FHZC_DIFFBUILD_CLEAR_H
