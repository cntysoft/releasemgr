#include <QProcess>
#include <QStringList>
#include <QChar>
#include <QDir>

#include "build_js_projects.h"
#include "task/abstract_taskmgr.h"
#include "kernel/errorinfo.h"
#include "io/filesystem.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

BuildJsProjects::BuildJsProjects(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs)
   :AbstractTask(taskmgr, invokeArgs)
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

}//fullbuild
}//fhzc
}//task
}//releasemgr