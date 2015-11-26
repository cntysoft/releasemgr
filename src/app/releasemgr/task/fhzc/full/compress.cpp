#include <QStringList>
#include <QDir>
#include <QChar>
#include <QProcess>
#include <QLatin1String>

#include "compress.h"
#include "kernel/errorinfo.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

Compress::Compress(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   :AbstractTask(taskmgr, invokeArgs)
{
}

void Compress::exec()
{
   writeBeginMsg("开始压缩项目文件 ... ");
   QString version = m_invokeArgs[QLatin1String("version")].toString();
   QStringList sourceDirs = getSysCfgValue("sourceDirs").toStringList();
   sourceDirs.append(QString("fenghuang_%1.sql").arg(version));
   execGzipCmd(QString("fenghuang_%1.tar.gz").arg(version), sourceDirs);
   writeDoneMsg();
}
void Compress::execGzipCmd(const QString& savedFilename, const QStringList &files)
{
   QProcess process;
   QStringList args;
   process.setWorkingDirectory(m_buildDir);
   args << "-czvf" << savedFilename << files;
   process.start("tar", args);
   bool status = process.waitForFinished(-1);
   if(!status || process.exitCode() != 0){
      throw ErrorInfo(process.errorString());
   }
}


Compress::~Compress()
{}

}//fullbuild
}//fhzc
}//task
}//releasemgr