#ifndef RELEASEMGR_TASK_CLOUD_CONTROLLER_TASKMGR_H
#define RELEASEMGR_TASK_CLOUD_CONTROLLER_TASKMGR_H

#include "task/abstract_taskmgr.h"

class Settings;
QT_BEGIN_NAMESPACE
class QLatin1String;
QT_END_NAMESPACE

namespace releasemgr{
namespace task{
namespace cloudcontroller{
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
}//cloudcontroller
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_CLOUD_CONTROLLER_TASKMGR_H
