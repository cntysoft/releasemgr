#include <QDir>
#include <QStringList>
#include <QFileInfo>
#include <QString>
#include <QFile>
#include <QByteArray>
#include <QChar>
#include <QLatin1String>
#include <QProcess>
#include <QRegularExpression>

#include "full_build_tasks.h"
#include "task/abstract_taskmgr.h"
#include "kernel/errorinfo.h"
#include "io/filesystem.h"
#include "utils/stddir.h"
#include "const.h"

namespace releasemgr{
namespace task{
namespace cloudcontrollerweb{
namespace fullbuild{

using sn::corelib::ErrorInfo;
using sn::corelib::Filesystem;

FullBuildAbstractTask::FullBuildAbstractTask(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   :AbstractTask(taskmgr, invokeArgs)
{
   m_buildDir = getSysCfgValue("webBuildDir").toString() + QDir::separator() + "cloudcontrollerweb_" + m_invokeArgs["version"];
   m_projectDir = getSysCfgValue("webProjectDir").toString();
}

FullBuildAbstractTask::~FullBuildAbstractTask()
{}


Clear::Clear(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs)
   :FullBuildAbstractTask(taskmgr, invokeArgs)
{}

void Clear::exec()
{
   writeBeginMsg("清除相关打包文件夹内容 ... ");
   QDir buildDir(m_buildDir);
   if(buildDir.exists()){
      if(!buildDir.removeRecursively()){
         throw ErrorInfo("delete build directory failure");
      }
   }
   writeDoneMsg();
}

Clear::~Clear()
{}


CopyProjectFiles::CopyProjectFiles(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs)
   :FullBuildAbstractTask(taskmgr, invokeArgs)
{}

void CopyProjectFiles::exec()
{
   writeBeginMsg("复制项目PHP部分文件夹 ... ");
   QDir buildDir(m_buildDir);
   if(!buildDir.exists()){
      if(!buildDir.mkpath(".")){
         throw ErrorInfo(QString("create build directory : %1 error").arg(m_buildDir));
      };
   }
   QStringList filenames;
   QChar ds = QDir::separator();
   //获取核心程序的文件集合
   Filesystem::traverseFs(m_projectDir+ds+"Library", 0, [&filenames](QFileInfo& fileInfo, int)->void{
      QString filename = fileInfo.absoluteFilePath();
      if(fileInfo.isFile() && !filename.contains("ReleaseTools")){
         filenames.append(filename);
      }
   });
   //获取指定的文件夹的文件集合
   QStringList specifyDirs{
            m_projectDir+ds+"Modules",
            m_projectDir+ds+"Apps",
            m_projectDir+ds+"Config",
            m_projectDir+ds+"SysApiHandler",
            m_projectDir+ds+"JsLibrary",
            m_projectDir+ds+"Data"+ds+"Framework",
            m_projectDir+ds+"Statics",
            m_projectDir+ds+"TagLibrary"
   };
   QStringList::const_iterator it = specifyDirs.cbegin();
   while(it != specifyDirs.cend()){
      Filesystem::traverseFs(*it, 0, [&filenames](QFileInfo& fileInfo, int)->void{
         if(fileInfo.isFile()){
            filenames.append(fileInfo.absoluteFilePath());
         }
      });
      it++;
   }
   collectSpecialFilenames(filenames);
   it = filenames.cbegin();
   while(it != filenames.cend()){
      QString sourceFilename(*it);
      QString destinationFilename(sourceFilename);
      destinationFilename.replace(m_projectDir, m_buildDir);
      Filesystem::copyFile(sourceFilename, destinationFilename);
      it++;
   }
   writeDoneMsg();
}

void CopyProjectFiles::collectSpecialFilenames(QStringList& filenames)
{
   QChar ds = QDir::separator();
   filenames.append(m_projectDir+ds+"index.php");
}

CopyProjectFiles::~CopyProjectFiles()
{}

GenerateVersionInfo::GenerateVersionInfo(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : FullBuildAbstractTask(taskmgr, invokeArgs)
{}

void GenerateVersionInfo::exec()
{
   writeBeginMsg("正在生成版本文件 ... ");
   QChar ds = QDir::separator();
   QFile versionTplFile(m_buildDir+ds+"Library"+ds+"CloudController"+ds+"Version.php");
   versionTplFile.open(QFile::ReadWrite);
   QByteArray content = versionTplFile.readAll();
   content.replace("{version}", m_invokeArgs["version"].toLatin1());
   versionTplFile.remove();
   QFile versionFile(m_buildDir+ds+"Library"+ds+"CloudController"+ds+"Version.php");
   versionFile.open(QFile::WriteOnly|QFile::Truncate);
   versionFile.write(content);
   writeDoneMsg();
}

GenerateVersionInfo::~GenerateVersionInfo()
{}

SetupDistConst::SetupDistConst(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : FullBuildAbstractTask(taskmgr, invokeArgs)
{}

void SetupDistConst::exec()
{
   writeBeginMsg("正在生成部署相关的常量 ... ");
   bool deployForAliyun = m_invokeArgs["aliyun"] == "true" ? true : false;
   QChar ds = QDir::separator();
   QString baseDir(StdDir::getAssetsDir()+ds+"cloudcontroller"+ds+"distconst");
   QString constFilename;
   if(deployForAliyun){
      constFilename = baseDir + ds + "AliyunDeployment.php";
   }else{
      constFilename = baseDir + ds + "NormalDeployment.php";
   }
   QString targetConstFilename = m_buildDir + ds + "Library" + ds + "CloudController" + ds + "DistConst.php";
   Filesystem::copyFile(constFilename, targetConstFilename, true);
   writeDoneMsg();
}

SetupDistConst::~SetupDistConst()
{}

BuildJsProjects::BuildJsProjects(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs)
   :FullBuildAbstractTask(taskmgr, invokeArgs)
{}

void BuildJsProjects::exec()
{
   writeBeginMsg("开始打包项目Js部分源码 ... \n");
   QStringList projects = getChildKeys("senchaProjects");
   auto it = projects.cbegin();
   QChar ds = QDir::separator();
   QString baseDir = m_projectDir+ds+"PlatformJs";
   while(it != projects.cend()){
      writeLine(QString("正在打包项目 : %1 ... ").arg(*it).toLocal8Bit(), TerminalColor::LightYellow, false);
      execSenchaCmd(baseDir+ds+(*it));
      writeDoneMsg();
      it++;
   }
   QString targetDir = m_projectDir+ds+"PlatformJs"+ds+"build"+ds+"production";
   QStringList files;
   Filesystem::traverseFs(targetDir, 0, [&files](QFileInfo& fileInfo, int){
      if(fileInfo.isFile()){
         files.append(fileInfo.absoluteFilePath());
      }
   });
   writeBeginMsg("开始复制打包结果文件 ... ");
   it = files.cbegin();
   while(it != files.cend()){
      QString source = *it;
      QString destination(source);
      destination.replace(m_projectDir, m_buildDir);
      Filesystem::copyFile(source, destination);
      it++;
   }
   writeDoneMsg();
}

void BuildJsProjects::execSenchaCmd(const QString &projectDir)
{
   QProcess process;
   QStringList args;
   process.setWorkingDirectory(projectDir);
   args << "app" << "build";
   process.start("sencha", args);
   bool status = process.waitForFinished(-1);
   if(!status || process.exitCode() != 0){
      throw ErrorInfo(process.errorString());
   }
}

BuildJsProjects::~BuildJsProjects()
{}

DumpMysql::DumpMysql(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   :FullBuildAbstractTask(taskmgr, invokeArgs)
{}

void DumpMysql::exec()
{
   writeBeginMsg("开始导出项目数据库 ... ");
   QChar ds = QDir::separator();
   QString savedFilename = m_buildDir+ds+"cloudcontrollerweb_"+m_invokeArgs["version"]+".sql";
   QString dbname = "cloudcontroller_" + m_invokeArgs["version"];
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
      throw ErrorInfo(process.errorString());
   }
   sql = process.readAll();
}

DumpMysql::~DumpMysql()
{}


SetupConfig::SetupConfig(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : FullBuildAbstractTask(taskmgr, invokeArgs)
{}

void SetupConfig::exec()
{
   writeBeginMsg("正在设置相关配置信息 ... ");
   QChar ds = QDir::separator();
   QString applicationCfgFilename(m_buildDir+ds+"Config"+ds+"Application.config.json");
   QString cfg = Filesystem::fileGetContents(applicationCfgFilename);
   cfg.replace(QRegularExpression("\"systemMode\"\\s*?:\\s*?2"), "'systemMode':1");
   Filesystem::filePutContents(applicationCfgFilename, cfg);
   writeDoneMsg();
}

SetupConfig::~SetupConfig()
{}


Compress::Compress(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   :FullBuildAbstractTask(taskmgr, invokeArgs)
{
}

void Compress::exec()
{
   writeBeginMsg("开始压缩项目文件 ... ");
   QString version = m_invokeArgs["version"];
   QString sourceDir = "cloudcontrollerweb_"+version;
   execGzipCmd(QString("cloudcontrollerweb_%1.tar.gz").arg(version), sourceDir);
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
}//cloudcontrollerweb
}//task
}//releasemgr