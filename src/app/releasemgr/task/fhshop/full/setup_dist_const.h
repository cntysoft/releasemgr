#ifndef RELEASEMGR_TASK_FHSHOP_FULLBUILD_SETUP_DIST_CONST_H
#define RELEASEMGR_TASK_FHSHOP_FULLBUILD_SETUP_DIST_CONST_H

#include "fullbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhshop{
namespace fullbuild{

class SetupDistConst : public FullBuildAbstractTask
{
public:
   SetupDistConst(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~SetupDistConst();
};

}//fullbuild
}//fhshop
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_FHSHOP_FULLBUILD_SETUP_DIST_CONST_H
