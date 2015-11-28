#include <QDir>

#include "diffbuild_abstract_task.h"
#include "task/abstract_taskmgr.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace diffbuild{


DiffBuildAbstractTask::DiffBuildAbstractTask(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   :AbstractTask(taskmgr, invokeArgs),
     m_from(m_invokeArgs[QLatin1String("from")].toString()),
     m_to(m_invokeArgs[QLatin1String("to")].toString())
{
   m_buildDir = m_buildDir + QDir::separator() + "fenghuang_patch_" + m_from +"_"+ m_to;
}

DiffBuildAbstractTask::~DiffBuildAbstractTask()
{}

}//diffbuild
}//fhzc
}//task
}//releasemgr
