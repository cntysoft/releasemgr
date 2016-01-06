#ifndef RELEASEMGR_TASK_CLOUD_CONTROLLER_RPM_BUILD_RPM
#define RELEASEMGR_TASK_CLOUD_CONTROLLER_RPM_BUILD_RPM

#include "rpmbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace cloudcontroller{
namespace rpmbuild{

class BuildRpm : public RpmBuildAbstractTask 
{
public:
   BuildRpm(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~BuildRpm();
};

}//rpmbuild
}//cloudcontroller
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_CLOUD_CONTROLLER_RPM_BUILD_RPM