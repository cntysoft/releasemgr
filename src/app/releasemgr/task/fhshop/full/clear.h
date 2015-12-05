#ifndef TASK_FHSHOP_FULLBUILD_CLEAR_H
#define TASK_FHSHOP_FULLBUILD_CLEAR_H

#include "fullbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhshop{
namespace fullbuild{

class Clear : public FullBuildAbstractTask
{
public:
   Clear(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~Clear();
};

}//fullbuild
}//fhshop
}//task
}//releasemgr

#endif // TASK_FHSHOP_FULLBUILD_CLEAR_H
