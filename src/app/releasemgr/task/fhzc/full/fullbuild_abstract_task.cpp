#include <QDir>
#include <QLatin1String>

#include "fullbuild_abstract_task.h"
#include "task/abstract_taskmgr.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

FullBuildAbstractTask::FullBuildAbstractTask(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   :AbstractTask(taskmgr, invokeArgs)
{
   m_buildDir = m_buildDir + QDir::separator() + "fenghuang_" + m_invokeArgs["version"];
}

FullBuildAbstractTask::~FullBuildAbstractTask()
{}

}//fullbuild
}//fhzc
}//task
}//releasemgr
