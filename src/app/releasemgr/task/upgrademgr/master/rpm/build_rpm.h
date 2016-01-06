#ifndef RELEASEMGR_TASK_RMMGR_RPM_BUILD_RPM
#define RELEASEMGR_TASK_RMMGR_RPM_BUILD_RPM

#include "rpmbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace upgrademgrmaster{
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
}//upgrademgrmaster
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_RMMGR_RPM_BUILD_RPM