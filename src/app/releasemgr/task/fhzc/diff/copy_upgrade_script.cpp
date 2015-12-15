#include "copy_upgrade_script.h"
#include "io/filesystem.h"
#include "const.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace diffbuild{

using sn::corelib::Filesystem;

CopyUpgradeScript::CopyUpgradeScript(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : DiffBuildAbstractTask(taskmgr, invokeArgs)
{
}

void CopyUpgradeScript::exec()
{
   writeBeginMsg("正在复制升级脚本文件 ... ");
   QString sourceFilename(m_projectDir+DS+"UpgradeEnv"+DS+"Scripts"+DS+"upgradescript_"+
                          m_from+"_"+m_to+".php");
   QString destinationFilename(sourceFilename);
   destinationFilename.replace(m_projectDir+DS+"UpgradeEnv"+DS+"Scripts", m_buildDir);
   if(QFileInfo(sourceFilename).exists()){
      Filesystem::copyFile(sourceFilename, destinationFilename);
   }
   writeDoneMsg();
}

CopyUpgradeScript::~CopyUpgradeScript()
{}

}//diffbuild
}//fhzc
}//task
}//releasemgr