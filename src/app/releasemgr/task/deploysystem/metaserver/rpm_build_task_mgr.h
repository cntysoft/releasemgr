#ifndef DEPLOY_SYSTEM_TASK_META_SERVER_RPM_BUILD_TASK_MGR_H
#define DEPLOY_SYSTEM_TASK_META_SERVER_RPM_BUILD_TASK_MGR_H

#include "task/abstract_taskmgr.h"
#include "types.h"

class Settings;
QT_BEGIN_NAMESPACE
class QLatin1String;
QT_END_NAMESPACE

namespace releasemgr{
namespace task{
namespace deploysystem{
namespace metaserver{
namespace rpmbuild{

using releasemgr::TaskParamsType;

class TaskMgr : public releasemgr::AbstractTaskMgr
{
public:
   TaskMgr(const QLatin1String& moduleName, Settings& settings);
protected:
   virtual void beforeRun(const TaskParamsType& args);
   virtual void afterRun(const TaskParamsType& args);
};

}//rpmbuild
}//metaserver
}//deploysystem
}//task
}//releasemgr

#endif // DEPLOY_SYSTEM_TASK_META_SERVER_RPM_BUILD_TASK_MGR_H