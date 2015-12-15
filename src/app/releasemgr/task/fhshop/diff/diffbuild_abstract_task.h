#ifndef RELEASEMGR_TASK_FHSHOP_DIFFBUILD_DIFFBUILD_ABSTRACT_TASK_H
#define RELEASEMGR_TASK_FHSHOP_DIFFBUILD_DIFFBUILD_ABSTRACT_TASK_H

#include "task/abstract_task.h"

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhshop{
namespace diffbuild{

class DiffBuildAbstractTask : public releasemgr::AbstractTask
{
public:
   DiffBuildAbstractTask(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
protected:
   QString m_from;
   QString m_to;
public:
   virtual ~DiffBuildAbstractTask();
};

}//diffbuild
}//fhshop
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_FHSHOP_DIFFBUILD_DIFFBUILD_ABSTRACT_TASK_H
