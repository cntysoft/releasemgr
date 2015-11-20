#include <QVariant>
#include <QDebug>
#include <QProcess>

#include "const.h"
#include "utils/env_detecter.h"
#include "settings.h"
#include "io/terminal.h"
#include "utils/funcs.h"
#include "application.h"
#include "kernel/errorinfo.h"

namespace releasemgr 
{

EnvDetecter::EnvDetecter(Settings& settings)
   : m_settings(settings)
{
}

void EnvDetecter::detect()
{
   if(!isNeedDetect()){
      return;
   }
   Terminal::writeText("detect build environment\n", TerminalColor::LightGreen);
   Terminal::writeText("begin detect git ...\n", TerminalColor::Default);
   if(!detectGit()){
      m_needInstalledTools << "git";
      Terminal::writeText("git not found\n", TerminalColor::Red);
   }
   Terminal::writeText("begin detect gzip ...\n", TerminalColor::Default);
   if(!detectGzip()){
      m_needInstalledTools << "gzip";
      Terminal::writeText("gzip not found\n", TerminalColor::Red);
   }
   Terminal::writeText("begin detect sencha ...\n", TerminalColor::Default);
   if(!detectSencha()){
      m_needInstalledTools << "sencha";
      Terminal::writeText("sencha not found\n", TerminalColor::Red);
   }
   if(!m_needInstalledTools.empty()){
      throw ErrorInfo("build enviroment tools not satisfy, please install them and try again");
   }
   //将探测结果写入配置文件
   m_settings.setValue(IS_DETECT_KEY, true);
   m_settings.sync();
}

bool EnvDetecter::detectGit()
{
   QProcess process;
   QStringList args;
   args << "--version";
   process.start("git", args);
   bool status = process.waitForFinished();
   if(!status){
      return status;
   }
   QByteArray ret = process.readAll();
   if(ret.startsWith("git version")){
      return true;
   }
   return false;
}

bool EnvDetecter::detectGzip()
{
   QProcess process;
   QStringList args;
   args << "--version";
   process.start("gzip", args);
   bool status = process.waitForFinished();
   if(!status){
      return status;
   }
   QByteArray ret = process.readAll();
   if(ret.startsWith("gzip")){
      return true;
   }
   return false;
}

bool EnvDetecter::detectSencha()
{
   QProcess process;
   process.start("sencha");
   bool status = process.waitForFinished();
   if(!status){
      return status;
   }
   QByteArray ret = process.readAll();
   if(ret.startsWith("Sencha Cmd")){
      return true;
   }
   return false;
}

bool EnvDetecter::isNeedDetect()const
{
   return !m_settings.getValue(IS_DETECT_KEY, CFG_GROUP_GLOABL, false).toBool();
}

}//releasemgr