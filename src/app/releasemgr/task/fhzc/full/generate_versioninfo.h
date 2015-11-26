#ifndef TASK_FHZC_FULLBUILD_GENERATE_VERSIONINFO_H
#define TASK_FHZC_FULLBUILD_GENERATE_VERSIONINFO_H

#include "task/abstract_task.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

class GenerateVersionInfo : public releasemgr::AbstractTask
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
