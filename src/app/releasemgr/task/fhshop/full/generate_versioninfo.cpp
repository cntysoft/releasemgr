#include <QString>
#include <QFile>
#include <QDir>
#include <QByteArray>
#include <QDebug>

#include "generate_versioninfo.h"
#include "task/abstract_taskmgr.h"

namespace releasemgr{
namespace task{
namespace fhshop{
namespace fullbuild{

GenerateVersionInfo::GenerateVersionInfo(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : FullBuildAbstractTask(taskmgr, invokeArgs)
{}

void GenerateVersionInfo::exec()
{
   writeBeginMsg("正在生成版本文件 ... ");
   QChar ds = QDir::separator();
   QFile versionTplFile(m_buildDir+ds+"Library"+ds+"FengHuang"+ds+"Version.php");
   versionTplFile.open(QFile::ReadWrite);
   QByteArray content = versionTplFile.readAll();
   content.replace("{version}", m_invokeArgs[QLatin1String("version")].toString().toLatin1());
   versionTplFile.remove();
   QFile versionFile(m_buildDir+ds+"Library"+ds+"FengHuang"+ds+"Version.php");
   versionFile.open(QFile::WriteOnly|QFile::Truncate);
   versionFile.write(content);
   writeDoneMsg();
}

GenerateVersionInfo::~GenerateVersionInfo()
{}

}//fullbuild
}//fhshop
}//task
}//releasemgr
