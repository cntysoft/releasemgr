#include <QDebug>
#include <QFileInfo>

#include "clear.h"
#include "task/abstract_taskmgr.h"
#include "io/filesystem.h"
#include "kernel/errorinfo.h"

namespace releasemgr{
namespace task{
namespace rmmgr{
namespace rpmbuild{

Clear::Clear(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs)
   :RpmBuildAbstractTask(taskmgr, invokeArgs)
{}

void Clear::exec()
{
   writeBeginMsg("开始清除打包目录 ... ");
   if(Filesystem::fileExist(m_buildDir)){
      if(!Filesystem::isWritable(m_buildDir)){
         throw ErrorInfo("build directory is no writable");
      }
      Filesystem::deleteDirRecusive(m_buildDir);
   }
   Filesystem::createPath(m_buildDir);
   writeDoneMsg();
}

Clear::~Clear()
{}

}//rpmbuild
}//rmmgr
}//task
}//releasemgr