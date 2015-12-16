#include <QDir>

#include "clear.h"
#include "task/abstract_taskmgr.h"
#include "kernel/errorinfo.h"

namespace releasemgr{
namespace task{
namespace fhshop{
namespace diffbuild{


using sn::corelib::ErrorInfo;

Clear::Clear(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : DiffBuildAbstractTask(taskmgr, invokeArgs)
{
}

void Clear::exec()
{
   writeBeginMsg("清除相关打包文件夹内容 ... ");
   QDir buildDir(m_buildDir);
   if(buildDir.exists()){
      if(!buildDir.removeRecursively()){
         throw ErrorInfo("delete build directory failure");
      }
   }
   writeDoneMsg();
}

Clear::~Clear()
{}

}//diffbuild
}//fhshop
}//task
}//releasemgr
