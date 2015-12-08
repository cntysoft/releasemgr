#ifndef TASK_RMMGR_RPM_COPY_SOURCE_FILES_H
#define TASK_RMMGR_RPM_COPY_SOURCE_FILES_H

#include "rpmbuild_abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace rmmgr{
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
}//rmmgr
}//task
}//releasemgr

#endif // TASK_RMMGR_RPM_COPY_SOURCE_FILES_H
