#ifndef TASK_RMMGR_RPM_MAKE_PROJECT_STRUCTURE_H
#define TASK_RMMGR_RPM_MAKE_PROJECT_STRUCTURE_H

#include "rpmbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace rmmgr{
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
}//rmmgr
}//task
}//releasemgr

#endif // TASK_RMMGR_RPM_MAKE_PROJECT_STRUCTURE_H
