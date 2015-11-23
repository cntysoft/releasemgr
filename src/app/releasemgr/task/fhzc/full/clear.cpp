#include <QDir>
#include <QDebug>

#include "clear.h"
#include "task/abstract_taskmgr.h"
#include "kernel/errorinfo.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

Clear::Clear(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs)
   :AbstractTask(taskmgr, invokeArgs)
{}

void Clear::exec()
{
   writeLine("清除相关打包文件夹内容 ... ");
   QDir buildDir(m_buildDir);
   if(buildDir.exists()){
      if(!buildDir.removeRecursively()){
         throw ErrorInfo("delete build directory failure");
      }
   }
}

Clear::~Clear()
{}

}//fullbuild
}//fhzc
}//task
}//releasemgr