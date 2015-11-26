#ifndef TASK_FHZC_FULLBUILD_BUID_COMPRESS_H
#define TASK_FHZC_FULLBUILD_BUID_COMPRESS_H

#include "task/abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

class Compress : public releasemgr::AbstractTask
{
public:
   Compress(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~Compress();
private:
   void execGzipCmd(const QString& savedFilename, const QStringList& files);
};

}//fullbuild
}//fhzc
}//task
}//releasemgr

#endif // TASK_FHZC_FULLBUILD_BUID_COMPRESS_H
