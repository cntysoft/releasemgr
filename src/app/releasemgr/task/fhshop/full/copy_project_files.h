#ifndef TASK_FHSHOP_FULLBUILD_COPY_PROJECT_FILES_H
#define TASK_FHSHOP_FULLBUILD_COPY_PROJECT_FILES_H

#include "fullbuild_abstract_task.h"

QT_BEGIN_NAMESPACE
class QStringList;
QT_END_NAMESPACE

namespace releasemgr{
namespace task{
namespace fhshop{
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
}//fhshop
}//task
}//releasemgr

#endif // TASK_FHSHOP_FULLBUILD_COPY_PROJECT_FILES_H
