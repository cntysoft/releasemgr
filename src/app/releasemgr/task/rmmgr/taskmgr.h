#ifndef TASK_RMMGR_TASKMGR_H
#define TASK_RMMGR_TASKMGR_H

#include "task/abstract_taskmgr.h"

QT_BEGIN_NAMESPACE
class QLatin1String;
QT_END_NAMESPACE

class Settings;

namespace releasemgr{
namespace task{
namespace rmmgr{
namespace fullbuild{

class TaskMgr : public releasemgr::AbstractTaskMgr
{
public:
   TaskMgr(const QLatin1String& moduleName, Settings& settings);
protected:
   virtual void beforeRun(const TaskParamsType& args);
   virtual void afterRun(const TaskParamsType& args);
};

}//fullbuild
}//rmmgr
}//task
}//releasemgr

#endif // TASK_RMMGR_TASKMGR_H
