#include <QDir>
#include <QChar>
#include <QLatin1String>
#include <QProcess>
#include <QStringList>

#include "dump_mysql.h"
#include "task/abstract_taskmgr.h"
#include "const.h"
#include "kernel/errorinfo.h"
#include "io/filesystem.h"

namespace releasemgr{
namespace task{
namespace fhshop{
namespace fullbuild{

using sn::corelib::Filesystem;
using sn::corelib::ErrorInfo;

DumpMysql::DumpMysql(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   :FullBuildAbstractTask(taskmgr, invokeArgs)
{}

void DumpMysql::exec()
{
   writeBeginMsg("开始导出项目数据库 ... ");
   QChar ds = QDir::separator();
   QString savedFilename = m_buildDir+ds+"fenghuangshop_"+m_invokeArgs["version"]+".sql";
   QString dbname = "fenghuangshop_" + m_invokeArgs["version"];
   QString sql;
   QString username = m_settings.getValue("db.username", CFG_GROUP_GLOBAL).toString();
   QString password = m_settings.getValue("db.password", CFG_GROUP_GLOBAL).toString();
   execMysqlDumpCmd(username, password, dbname, sql, false);
   Filesystem::filePutContents(savedFilename, sql);
   writeDoneMsg();
}

void DumpMysql::execMysqlDumpCmd(const QString &username, const QString &password, const QString &dbname, QString& sql, bool withData)
{
   QProcess process;
   QStringList args;
   args << QString("-u%1").arg(username) << QString("-p%1").arg(password);
   if(withData){
      args << "-d";
   }
   args << dbname;
   process.start("mysqldump", args);
   bool status = process.waitForFinished(-1);
   if(!status || process.exitCode() != 0){
      throw ErrorInfo(process.readAll());
   }
   sql = process.readAll();
}

DumpMysql::~DumpMysql()
{}

}//fullbuild
}//fhshop
}//task
}//releasemgr
