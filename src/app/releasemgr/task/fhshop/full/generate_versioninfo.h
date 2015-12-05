#ifndef TASK_FHSHOP_FULLBUILD_GENERATE_VERSIONINFO_H
#define TASK_FHSHOP_FULLBUILD_GENERATE_VERSIONINFO_H

#include "fullbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhshop{
namespace fullbuild{

class GenerateVersionInfo : public FullBuildAbstractTask
{
public:
   GenerateVersionInfo(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~GenerateVersionInfo();
};

}//fullbuild
}//fhshop
}//task
}//releasemgr

#endif // TASK_FHSHOP_FULLBUILD_GENERATE_VERSIONINFO_H
