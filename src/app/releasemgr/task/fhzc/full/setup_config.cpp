#include <QDir>
#include <QChar>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "setup_config.h"
#include "task/abstract_taskmgr.h"
#include "io/filesystem.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

using sn::corelib::Filesystem;

SetupConfig::SetupConfig(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : FullBuildAbstractTask(taskmgr, invokeArgs)
{}

void SetupConfig::exec()
{
   writeBeginMsg("正在设置相关配置信息 ... ");
   QChar ds = QDir::separator();
   QString applicationCfgFilename(m_buildDir+ds+"Config"+ds+"Application.config.php");
   QString cfg = Filesystem::fileGetContents(applicationCfgFilename);
   cfg.replace(QRegularExpression("[\"\']systemMode[\'\"]\\s*?=>\\s*?2"), "'systemMode' => 1");
   Filesystem::filePutContents(applicationCfgFilename, cfg);
   writeDoneMsg();
}

SetupConfig::~SetupConfig()
{}

}//fullbuild
}//fhzc
}//task
}//releasemgr
