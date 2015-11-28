#ifndef TASK_FHZC_DIFFBUILD_GENERATE_DIFF_METAINFO_H
#define TASK_FHZC_DIFFBUILD_GENERATE_DIFF_METAINFO_H

#include "diffbuild_abstract_task.h"

class AbstractTaskMgr;

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

namespace releasemgr{
namespace task{
namespace fhzc{
namespace diffbuild{

class GenerateDiffMetaInfo : public DiffBuildAbstractTask
{
public:
   GenerateDiffMetaInfo(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~GenerateDiffMetaInfo();
private:
   void collectModifiedSubmodules(QStringList& submodules);
private:
   bool m_needRunSenchaCmd = false;
};

}//diffbuild
}//fhzc
}//task
}//releasemgr

#endif // TASK_FHZC_DIFFBUILD_GENERATE_DIFF_METAINFO_H
