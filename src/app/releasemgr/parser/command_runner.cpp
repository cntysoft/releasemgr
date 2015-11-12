#include "Command_runner.h"
#include "application.h"
#include "kernel/errorinfo.h"
#include "Command/Command_category.h"
#include <QCommandLineParser>
#include <QLatin1String>

namespace releasemgr
{

CommandRunner::CommandRunner(const Application &app)
   :app(app)
{
}

void CommandRunner::run()
{
   //检查子命令的类型
   QStringList args = app.arguments();
   if(args.count() < 2){
      printUsage();
      throw ErrorInfo();
   }
   QStringList targetArgs{args.at(0)};
   QString first = args.at(1);
   QCommandLineParser* parser = nullptr;
   CommandCategory cmdCategory = CommandCategory::Unknow;
   CommandName cmdName = CommandName::Unknow;
   if(first.startsWith(QLatin1String("--"))){
      //匹配顶层Commandparser
      targetArgs.append(first);
      parser = optionPool.getEntryCmdParser();
      cmdCategory = CommandCategory::Global;
      OptionPool::OptionMapType opts = optionPool.getEntryOptions();
      if(parser->isSet(opts["version"])){
         cmdName = CommandName::Global_Version;
      }else if(parser->isSet(opts["help"])){
         cmdName = CommandName::Global_Help;
      }
   }else{
      //匹配子命令的Commandparser
      //查看子命令类型
         
   }
   
   qDebug() << first;
   
}

void CommandRunner::runCmd(const CommandMeta &meta)
{
   
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

QCommandLineParser* CommandRunner::getCmdParserByType(const char* t)
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
