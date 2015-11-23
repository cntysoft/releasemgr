#ifndef TASK_FHZC_FULLBUILD_COPY_PROJECT_FILES_H
#define TASK_FHZC_FULLBUILD_COPY_PROJECT_FILES_H

#include "task/abstract_task.h"

class AbstractTaskMgr;

QT_BEGIN_NAMESPACE
class QStringList;
QT_END_NAMESPACE

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

class CopyProjectFiles : public releasemgr::AbstractTask
{
public:
   CopyProjectFiles(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~CopyProjectFiles();
private:
   QStringList collectProjectFilenames();
};

}//fullbuild
}//fhzc
}//task
}//releasemgr

#endif // TASK_FHZC_FULLBUILD_COPY_PROJECT_FILES_H
