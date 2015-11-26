#ifndef TASK_FHZC_FULLBUILD_SETUP_CONFIG_H
#define TASK_FHZC_FULLBUILD_SETUP_CONFIG_H

#include "task/abstract_task.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

class SetupConfig : public releasemgr::AbstractTask
{
public:
   SetupConfig(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~SetupConfig();
};

}//fullbuild
}//fhzc
}//task
}//releasemgr

#endif // TASK_FHZC_FULLBUILD_SETUP_CONFIG_H
