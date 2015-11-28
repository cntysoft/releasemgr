#include <QStringList>

#include "generate_diff_metainfo.h"
#include "task/abstract_taskmgr.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace diffbuild{

GenerateDiffMetaInfo::GenerateDiffMetaInfo(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : DiffBuildAbstractTask(taskmgr, invokeArgs)
{}

void GenerateDiffMetaInfo::exec()
{
   writeBeginMsg("开始生成差异性元信息 ... ");
   QStringList submodules;
   collectModifiedSubmodules(submodules);
   writeDoneMsg();
}

void GenerateDiffMetaInfo::collectModifiedSubmodules(QStringList &submodules)
{
   writeMsg("\n开始分析改动的submodules数据 ... ", TerminalColor::LightYellow);
   
   writeDoneMsg();
}

GenerateDiffMetaInfo::~GenerateDiffMetaInfo()
{}

}//diffbuild
}//fhzc
}//task
}//releasemgr