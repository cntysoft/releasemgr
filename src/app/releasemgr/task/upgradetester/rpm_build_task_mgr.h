#ifndef RELEASEMGR_TASK_UPGRADE_TESTER_RPM_BUILD_TASK_MGR_H
#define RELEASEMGR_TASK_UPGRADE_TESTER_RPM_BUILD_TASK_MGR_H

#include "task/abstract_taskmgr.h"

class Settings;
QT_BEGIN_NAMESPACE
class QLatin1String;
QT_END_NAMESPACE

namespace releasemgr{
namespace task{
namespace upgradetester{
namespace rpmbuild{

class TaskMgr : public releasemgr::AbstractTaskMgr
{
public:
   TaskMgr(const QLatin1String& moduleName, Settings& settings);
protected:
   virtual void beforeRun(const TaskParamsType& args);
   virtual void afterRun(const TaskParamsType& args);
};

}//rpmbuild
}//upgradetester
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_UPGRADE_TESTER_RPM_BUILD_TASK_MGR_H
