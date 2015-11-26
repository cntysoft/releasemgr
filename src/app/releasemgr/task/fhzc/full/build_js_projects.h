#ifndef TASK_FHZC_FULLBUILD_BUID_JS_PROJECTS_H
#define TASK_FHZC_FULLBUILD_BUID_JS_PROJECTS_H

#include "task/abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

class BuildJsProjects : public releasemgr::AbstractTask
{
public:
   BuildJsProjects(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~BuildJsProjects();
private:
   void execSenchaCmd(const QString& projectDir);
};

}//fullbuild
}//fhzc
}//task
}//releasemgr

#endif // TASK_FHZC_FULLBUILD_BUID_JS_PROJECTS_H
