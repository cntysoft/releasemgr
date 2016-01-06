#ifndef RELEASEMGR_TASK_UPGRADEMGR_MASTER_RPM_CLEAR_H
#define RELEASEMGR_TASK_UPGRADEMGR_MASTER_RPM_CLEAR_H

#include "rpmbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace upgrademgrmaster{
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
}//upgrademgrmaster
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_UPGRADEMGR_MASTER_RPM_CLEAR_H
