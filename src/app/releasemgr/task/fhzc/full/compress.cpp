#include <QStringList>
#include <QDir>
#include <QFileInfo>
#include <QChar>
#include <QProcess>
#include <QLatin1String>

#include "compress.h"
#include "kernel/errorinfo.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

using sn::corelib::ErrorInfo;

Compress::Compress(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   :FullBuildAbstractTask(taskmgr, invokeArgs)
{
}

void Compress::exec()
{
   writeBeginMsg("开始压缩项目文件 ... ");
   QString version = m_invokeArgs["version"];
   QString sourceDir = "fenghuang_"+version;
   execGzipCmd(QString("fenghuang_%1.tar.gz").arg(version), sourceDir);
   writeDoneMsg();
}
void Compress::execGzipCmd(const QString& savedFilename, const QString &sourceDir)
{
   QProcess process;
   QStringList args;
   process.setWorkingDirectory(QFileInfo(m_buildDir).absolutePath());
   args << "-czvf" << savedFilename << sourceDir;
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
