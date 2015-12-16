#ifndef RELEASEMGR_TASK_FHSHOP_DIFFBUILD_COPY_UPGRADE_SCRIPT_H
#define RELEASEMGR_TASK_FHSHOP_DIFFBUILD_COPY_UPGRADE_SCRIPT_H

#include "diffbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhshop{
namespace diffbuild{

class CopyUpgradeScript : public DiffBuildAbstractTask
{
public:
   CopyUpgradeScript(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~CopyUpgradeScript();
};

}//diffbuild
}//fhshop
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_FHSHOP_DIFFBUILD_COPY_UPGRADE_SCRIPT_H
