#ifndef TASK_RMMGR_RPM_RPMBUILD_ABSTRACT_TASK_H
#define TASK_RMMGR_RPM_RPMBUILD_ABSTRACT_TASK_H

#include "task/abstract_task.h"

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace rmmgr{
namespace rpmbuild{

class RpmBuildAbstractTask : public releasemgr::AbstractTask
{
public:
   RpmBuildAbstractTask(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual ~RpmBuildAbstractTask();
protected:
   virtual QString getAssetDir();
protected:
   QString m_rpmSourceDir;
   QString m_rpmBuildDir;
   QString m_rpmSpecDir;
   QString m_rpmRpmDir;
   QString m_rpmSRpmDir;
   QString m_rpmBuildRootDir;
};

}//rpmbuild
}//rmmgr
}//task
}//releasemgr

#endif // TASK_RMMGR_RPM_RPMBUILD_ABSTRACT_TASK_H
