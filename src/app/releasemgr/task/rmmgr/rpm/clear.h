#ifndef TASK_RMMGR_RPM_CLEAR_H
#define TASK_RMMGR_RPM_CLEAR_H

#include "rpmbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace rmmgr{
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
}//rmmgr
}//task
}//releasemgr

#endif // TASK_RMMGR_RPM_CLEAR_H
