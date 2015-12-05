#ifndef TASK_FHSHOP_FULLBUILD_TASKMGR_H
#define TASK_FHSHOP_FULLBUILD_TASKMGR_H

#include "task/abstract_taskmgr.h"

QT_BEGIN_NAMESPACE
class QLatin1String;
QT_END_NAMESPACE

class Settings;

namespace releasemgr{
namespace task{
namespace fhshop{
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
}//fhshop
}//task
}//releasemgr

#endif // TASK_FHSHOP_FULLBUILD_TASKMGR_H
