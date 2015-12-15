#ifndef RELEASEMGR_TASK_FHZC_FULLBUILD_COPY_PROJECT_FILES_H
#define RELEASEMGR_TASK_FHZC_FULLBUILD_COPY_PROJECT_FILES_H

#include "fullbuild_abstract_task.h"

QT_BEGIN_NAMESPACE
class QStringList;
QT_END_NAMESPACE

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

class CopyProjectFiles : public FullBuildAbstractTask
{
public:
   CopyProjectFiles(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~CopyProjectFiles();
private:
   QStringList collectProjectFilenames();
   void collectSpecialFilenames(QStringList& filenames);
};

}//fullbuild
}//fhzc
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_FHZC_FULLBUILD_COPY_PROJECT_FILES_H
