#ifndef RELEASEMGR_TASK_FHSHOP_FULLBUILD_BUID_COMPRESS_H
#define RELEASEMGR_TASK_FHSHOP_FULLBUILD_BUID_COMPRESS_H

#include "fullbuild_abstract_task.h"

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhshop{
namespace fullbuild{

class Compress : public FullBuildAbstractTask
{
public:
   Compress(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~Compress();
private:
   void execGzipCmd(const QString& savedFilename, const QString& sourceDir);
};

}//fullbuild
}//fhshop
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_FHSHOP_FULLBUILD_BUID_COMPRESS_H
