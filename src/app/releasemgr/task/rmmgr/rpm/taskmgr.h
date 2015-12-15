#ifndef RELEASEMGR_TASK_RMMGR_RPM_TASKMGR_H
#define RELEASEMGR_TASK_RMMGR_RPM_TASKMGR_H

#include "task/abstract_taskmgr.h"

QT_BEGIN_NAMESPACE
class QLatin1String;
QT_END_NAMESPACE

class Settings;

namespace releasemgr{
namespace task{
namespace rmmgr{
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
}//rmmgr
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_RMMGR_RPM_TASKMGR_H
