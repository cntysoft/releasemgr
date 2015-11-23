#ifndef TASK_FHZC_FULLBUILD_TASKMGR_H
#define TASK_FHZC_FULLBUILD_TASKMGR_H

#include "task/abstract_taskmgr.h"
QT_BEGIN_NAMESPACE
class QLatin1String;
QT_END_NAMESPACE

class Settings;

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

class TaskMgr : public releasemgr::AbstractTaskMgr
{
public:
   TaskMgr(const QLatin1String& moduleName, Settings& settings);
};

}//fullbuild
}//fhzc
}//task
}//releasemgr

#endif // TASK_FHZC_FULLBUILD_TASKMGR_H
