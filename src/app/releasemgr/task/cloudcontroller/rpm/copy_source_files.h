#ifndef RELEASEMGR_TASK_CLOUD_CONTROLLER_RPM_COPY_SOURCE_FILES_H
#define RELEASEMGR_TASK_CLOUD_CONTROLLER_RPM_COPY_SOURCE_FILES_H

#include "rpmbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace cloudcontroller{
namespace rpmbuild{

class CopySourceFiles : public RpmBuildAbstractTask 
{
public:
   CopySourceFiles(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~CopySourceFiles();
private:
   void processSpecFile();
};

}//rpmbuild
}//cloudcontroller
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_CLOUD_CONTROLLER_RPM_COPY_SOURCE_FILES_H
