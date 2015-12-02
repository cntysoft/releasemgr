#ifndef TASK_FHZC_FULLBUILD_GENERATE_VERSIONINFO_H
#define TASK_FHZC_FULLBUILD_GENERATE_VERSIONINFO_H

#include "fullbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhzc{
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
}//fhzc
}//task
}//releasemgr

#endif // TASK_FHZC_FULLBUILD_GENERATE_VERSIONINFO_H
