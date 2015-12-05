#ifndef TASK_FHSHOP_FULLBUILD_BUID_JS_PROJECTS_H
#define TASK_FHSHOP_FULLBUILD_BUID_JS_PROJECTS_H

#include "fullbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhshop{
namespace fullbuild{

class BuildJsProjects : public FullBuildAbstractTask
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
}//fhshop
}//task
}//releasemgr

#endif // TASK_FHSHOP_FULLBUILD_BUID_JS_PROJECTS_H
