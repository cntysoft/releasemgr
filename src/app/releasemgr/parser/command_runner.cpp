#include "command_runner.h"
#include "application.h"
#include "kernel/errorinfo.h"
#include <QCommandLineParser>
#include <QLatin1String>

namespace releasemgr
{

CommandRunner::CommandRunner(const Application &app)
   :app(app)
{
}

void CommandRunner::run() const
{
   //检查子命令的类型
   QStringList args = app.arguments();
   if(args.count() < 2){
      printUsage();
      throw ErrorInfo();
   }
   QString subcommand = args.at(1);
   
}

QStringList CommandRunner::getSupportSubCommands()const
{
   return {
      "fhzc",
      "fhshop",
      "kelemall"
   };
}

void CommandRunner::printUsage()const
{
   return qDebug("welcome to use sheneninfo release manager system\n\n"
                  "usage: \nreleasemgr --version \t print main system version number\n"
                  "releasemgr --help \t print help document\n");
}

QCommandLineParser& CommandRunner::getCmdParserByType(const char* t)
{
   QLatin1String type(t);
   if(type == "fhzc"){
      return optionPool.getFhzcCmdParser();
   }else{
      return optionPool.getFhzcCmdParser();
   }
}

CommandRunner::~CommandRunner()
{
}

}//releasemgr
