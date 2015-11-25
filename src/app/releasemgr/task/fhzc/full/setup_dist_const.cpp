#include "setup_dist_const.h"
#include "task/abstract_taskmgr.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

SetupDistConst::SetupDistConst(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : AbstractTask(taskmgr, invokeArgs)
{}

void SetupDistConst::exec()
{
   writeBeginMsg("正在生成部署相关的常量 ... ");
   writeDoneMsg();
}

SetupDistConst::~SetupDistConst()
{}

}//fullbuild
}//fhzc
}//task
}//releasemgr