#ifndef TASK_FHSHOP_FULLBUILD_SETUP_CONFIG_H
#define TASK_FHSHOP_FULLBUILD_SETUP_CONFIG_H

#include "fullbuild_abstract_task.h"

namespace releasemgr{
namespace task{
namespace fhshop{
namespace fullbuild{

class SetupConfig : public FullBuildAbstractTask
{
public:
   SetupConfig(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~SetupConfig();
};

}//fullbuild
}//fhshop
}//task
}//releasemgr

#endif // TASK_FHSHOP_FULLBUILD_SETUP_CONFIG_H
