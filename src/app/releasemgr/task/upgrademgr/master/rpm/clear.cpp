#include <QFileInfo>

#include "clear.h"
#include "task/abstract_taskmgr.h"
#include "io/filesystem.h"
#include "kernel/errorinfo.h"

namespace releasemgr{
namespace task{
namespace upgrademgrmaster{
namespace rpmbuild{

using sn::corelib::Filesystem;
using sn::corelib::ErrorInfo;

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
}//upgrademgrmaster
}//task
}//releasemgr