#include <QStringList>
#include <QDir>
#include <QFileInfo>
#include <QChar>
#include <QProcess>
#include <QLatin1String>

#include "compress.h"
#include "kernel/errorinfo.h"
#include "const.h"

namespace releasemgr{
namespace task{
namespace fhshop{
namespace diffbuild{

using sn::corelib::ErrorInfo;

Compress::Compress(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   :DiffBuildAbstractTask(taskmgr, invokeArgs)
{
}

void Compress::exec()
{
   writeBeginMsg("开始压缩项目文件 ... ");
   QString sourceDirName = QString("fenghuangshop_%1_%2").arg(m_from, m_to);
   execGzipCmd(sourceDirName+".tar.gz", sourceDirName);
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

}//diffbuild
}//fhshop
}//task
}//releasemgr