#include <QStringList>
#include <QStringListIterator>

#include "make_project_structure.h"
#include "task/abstract_taskmgr.h"
#include "const.h"
#include "io/filesystem.h"

namespace releasemgr{
namespace task{
namespace upgrademgrmaster{
namespace rpmbuild{

using sn::corelib::Filesystem;

MakeProjectStructure::MakeProjectStructure(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : RpmBuildAbstractTask(taskmgr, invokeArgs)
{}

void MakeProjectStructure::exec()
{
   writeBeginMsg("开始创建RPM打包文件目录结构 ... ");
   QStringList dirs{
      m_rpmBuildDir,
            m_rpmRpmDir,
            m_rpmSourceDir,
            m_rpmSpecDir,
            m_rpmSRpmDir,
            m_rpmBuildRootDir
   };
   QStringListIterator iterator(dirs);
   while (iterator.hasNext()) {
      Filesystem::createPath(iterator.next());
   }
   writeDoneMsg();
}

MakeProjectStructure::~MakeProjectStructure()
{}

}//rpmbuild
}//upgrademgrmaster
}//task
}//releasemgr