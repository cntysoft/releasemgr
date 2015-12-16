#ifndef RELEASEMGR_TASK_FHSHOP_DIFFBUILD_SETUP_DIST_CONST_H
#define RELEASEMGR_TASK_FHSHOP_DIFFBUILD_SETUP_DIST_CONST_H

#include "diffbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhshop{
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
}//fhshop
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_FHSHOP_DIFFBUILD_SETUP_DIST_CONST_H
