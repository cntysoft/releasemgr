#include <QDir>

#include "diffbuild_abstract_task.h"
#include "task/abstract_taskmgr.h"

namespace releasemgr{
namespace task{
namespace fhshop{
namespace diffbuild{


DiffBuildAbstractTask::DiffBuildAbstractTask(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs)
   :AbstractTask(taskmgr, invokeArgs),
     m_from(m_invokeArgs["from"]),
     m_to(m_invokeArgs["to"])
{
   m_buildDir = m_buildDir + QDir::separator() + "fenghuangshop_" + m_from +"_"+ m_to;
}

DiffBuildAbstractTask::~DiffBuildAbstractTask()
{}

}//diffbuild
}//fhshop
}//task
}//releasemgr
