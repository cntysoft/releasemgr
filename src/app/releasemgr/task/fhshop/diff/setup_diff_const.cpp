#include <QDir>
#include <QChar>
#include <QLatin1String>

#include "setup_dist_const.h"
#include "task/abstract_taskmgr.h"
#include "utils/stddir.h"
#include "io/filesystem.h"

namespace releasemgr{
namespace task{
namespace fhshop{
namespace diffbuild{

using sn::corelib::Filesystem;

SetupDistConst::SetupDistConst(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : DiffBuildAbstractTask(taskmgr, invokeArgs)
{}

void SetupDistConst::exec()
{
   writeBeginMsg("正在生成部署相关的常量 ... ");
   bool deployForAliyun = m_invokeArgs["aliyun"] == "true" ? true : false;
   QChar ds = QDir::separator();
   QString baseDir(StdDir::getAssetsDir()+ds+"fhshop"+ds+"distconst");
   QString constFilename;
   if(deployForAliyun){
      constFilename = baseDir + ds + "AliyunDeployment.php";
   }else{
      constFilename = baseDir + ds + "NormalDeployment.php";
   }
   QString targetConstFilename = m_buildDir + ds + "Library" + ds + "FengHuang" + ds + "DistConst.php";
   Filesystem::copyFile(constFilename, targetConstFilename, true);
   writeDoneMsg();
}

SetupDistConst::~SetupDistConst()
{}

}//diffbuild
}//fhshop
}//task
}//releasemgr