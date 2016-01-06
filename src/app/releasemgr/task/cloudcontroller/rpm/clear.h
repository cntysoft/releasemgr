#ifndef RELEASEMGR_TASK_CLOUD_CONTROLLER_RPM_CLEAR_H
#define RELEASEMGR_TASK_CLOUD_CONTROLLER_RPM_CLEAR_H

#include "rpmbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace cloudcontroller{
namespace rpmbuild{

class Clear : public RpmBuildAbstractTask
{
public:
   Clear(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~Clear();
};

}//rpmbuild
}//cloudcontroller
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_CLOUD_CONTROLLER_RPM_CLEAR_H
