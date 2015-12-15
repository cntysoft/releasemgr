#include <QDir>
#include <QFile>

#include "generate_versioninfo.h"
#include "task/abstract_taskmgr.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace diffbuild{

GenerateVersionInfo::GenerateVersionInfo(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : DiffBuildAbstractTask(taskmgr, invokeArgs)
{}

void GenerateVersionInfo::exec()
{
   writeBeginMsg("正在生成版本文件 ... ");
   QChar ds = QDir::separator();
   QFile versionTplFile(m_buildDir+ds+"Library"+ds+"FengHuang"+ds+"Version.php");
   versionTplFile.open(QFile::ReadWrite);
   QByteArray content = versionTplFile.readAll();
   content.replace("{version}", m_invokeArgs["version"].toLatin1());
   versionTplFile.remove();
   QFile versionFile(m_buildDir+ds+"Library"+ds+"FengHuang"+ds+"Version.php");
   versionFile.open(QFile::WriteOnly|QFile::Truncate);
   versionFile.write(content);
   writeDoneMsg();
}

GenerateVersionInfo::~GenerateVersionInfo()
{}

}//diffbuild
}//fhzc
}//task
}//releasemgr