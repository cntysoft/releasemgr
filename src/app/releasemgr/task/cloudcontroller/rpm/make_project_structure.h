#ifndef RELEASEMGR_TASK_CLOUD_CONTROLLER_RPM_MAKE_PROJECT_STRUCTURE_H
#define RELEASEMGR_TASK_CLOUD_CONTROLLER_RPM_MAKE_PROJECT_STRUCTURE_H

#include "rpmbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace cloudcontroller{
namespace rpmbuild{

class MakeProjectStructure : public RpmBuildAbstractTask 
{
public:
   MakeProjectStructure(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~MakeProjectStructure();
};

}//rpmbuild
}//cloudcontroller
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_CLOUD_CONTROLLER_RPM_MAKE_PROJECT_STRUCTURE_H
