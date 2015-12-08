#ifndef TASK_RMMGR_RPM_BUILD_RPM
#define TASK_RMMGR_RPM_BUILD_RPM

#include "rpmbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace rmmgr{
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
}//rmmgr
}//task
}//releasemgr

#endif // TASK_RMMGR_RPM_BUILD_RPM

