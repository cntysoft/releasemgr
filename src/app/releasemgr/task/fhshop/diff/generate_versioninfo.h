#ifndef RELEASEMGR_TASK_FHSHOP_DIFFBUILD_GENERATE_VERSIONINFO_H
#define RELEASEMGR_TASK_FHSHOP_DIFFBUILD_GENERATE_VERSIONINFO_H

#include "diffbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhshop{
namespace diffbuild{


class GenerateVersionInfo : public DiffBuildAbstractTask
{
public:
   GenerateVersionInfo(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~GenerateVersionInfo();
};

}//diffbuild
}//fhshop
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_FHSHOP_DIFFBUILD_GENERATE_VERSIONINFO_H
