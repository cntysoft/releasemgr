#include "clear.h"
#include "task/abstract_taskmgr.h"

#include <QDebug>

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

Clear::Clear(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs)
   :AbstractTask(taskmgr, invokeArgs)
{}

void Clear::exec()
{
   writeLine("clear project directory");
}

Clear::~Clear()
{}

}//fullbuild
}//fhzc
}//task
}//releasemgr