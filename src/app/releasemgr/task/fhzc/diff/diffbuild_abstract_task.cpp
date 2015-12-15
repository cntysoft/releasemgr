#include <QDir>

#include "diffbuild_abstract_task.h"
#include "task/abstract_taskmgr.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace diffbuild{


DiffBuildAbstractTask::DiffBuildAbstractTask(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   :AbstractTask(taskmgr, invokeArgs),
     m_from(m_invokeArgs["from"]),
     m_to(m_invokeArgs["to"])
{
   m_buildDir = m_buildDir + QDir::separator() + "fenghuang_" + m_from +"_"+ m_to;
}

DiffBuildAbstractTask::~DiffBuildAbstractTask()
{}

}//diffbuild
}//fhzc
}//task
}//releasemgr
