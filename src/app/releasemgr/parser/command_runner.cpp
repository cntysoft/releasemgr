#include "command_runner.h"
#include "application.h"
#include "kernel/errorinfo.h"
#include "command/command_category.h"
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QLatin1String>
#include <QDebug>

#include <QScopedPointer>
#include "command/abstract_command.h"
#include "command/command_repo.h"

namespace releasemgr
{

CommandRunner::CommandRunner(const Application &app)
   :m_app(app)
{
}

const CommandRunner::CmdPoolType CommandRunner::m_cmdRegisterPool{
   {CommandName::Global_Help,[](CommandRunner* runner)->AbstractCommand*{
         GlobalHelpCommand* cmd = new GlobalHelpCommand();
         cmd->setCommandRunner(runner);
         return cmd;
      }},
   {CommandName::Global_Version, [](CommandRunner* runner)->AbstractCommand*{
         GlobalVersionCommand* cmd = new GlobalVersionCommand();
         cmd->setCommandRunner(runner);
         return cmd;
      }},
   {CommandName::Fhzc_Build, [](CommandRunner* runner)->AbstractCommand*{
         FhzcBuildCommand* cmd = new FhzcBuildCommand();
         cmd->setCommandRunner(runner);
         return cmd;
      }}
};

const CommandRunner::CmdNameRepoType CommandRunner::m_subCmdNameMap{
   {"fhzc", CommandName::Fhzc_Build}
};

void CommandRunner::run()
{
   //检查子命令的类型
   QStringList args = m_app.arguments();
   if(args.count() < 2){
      printUsage();
      throw ErrorInfo();
   }
   QStringList targetArgs;
   QString first = args.at(1);
   CommandMeta::CmdArgType cmdArgs;
   QCommandLineParser* parser = nullptr;
   CommandCategory cmdCategory = CommandCategory::Unknow;
   CommandName cmdName = CommandName::Unknow;
   if(first.startsWith(QLatin1String("--"))){
      //匹配顶层Commandparser
      targetArgs.append(args.at(0));
      targetArgs.append(first);
      parser = m_optionPool.getEntryCmdParser();
      parser->parse(targetArgs);
      cmdCategory = CommandCategory::Global;
      OptionPool::OptionMapType opts = m_optionPool.getEntryOptions();
      if(parser->isSet(*opts["version"])){
         cmdName = CommandName::Global_Version;
      }else if(parser->isSet(*opts["help"])){
         cmdName = CommandName::Global_Help;
      }
   }else{
      //匹配子命令的Commandparser
      //查看子命令类型
      if(!isSubCmdSupported(first)){
         throw ErrorInfo(QString("sub command %1 is not supported").arg(first), CodeLocation(__FILE__, __LINE__));
      }
      args.removeFirst();
      QStringList::const_iterator it = args.cbegin();
      while(it != args.cend()){
         targetArgs.append(*it);
         it++;
      }
      cmdName = m_subCmdNameMap[first];
      cmdArgs = parseSubCmdArgs(cmdName, targetArgs);
   }
   runCmd(CommandMeta(cmdCategory, cmdName, cmdArgs));
}

CommandMeta::CmdArgType CommandRunner::parseSubCmdArgs(CommandName command, const QStringList& invokeArgs)
{
   QCommandLineParser* parser = nullptr;
   CommandMeta::CmdArgType args;
   switch (command) {
   case CommandName::Fhzc_Build:
   {
      parser = m_optionPool.getFhzcCmdParser();
      parser->process(invokeArgs);
      OptionPool::OptionMapType opts = m_optionPool.getFhzcOptions();
      QStringList positionArgs = parser->positionalArguments();
      if(1 != positionArgs.count()){
         
      }
      break;
   }
   default:
      break;
   }
   return args;
}


void CommandRunner::runCmd(const CommandMeta &meta)
{
   AbstractCommand* (*initializer)(CommandRunner*) = m_cmdRegisterPool[meta.getCommandName()];
   QScopedPointer<AbstractCommand> cmd(initializer(this));
   cmd->exec();
}

QList<QString> CommandRunner::getSupportSubCommands()const
{
   return m_subCmdNameMap.keys();
}

bool CommandRunner::isSubCmdSupported(const QString& cmd) const
{
   QList<QString> cmds = getSupportSubCommands();
   return cmds.contains(cmd);
}

void CommandRunner::printUsage()const
{
   return qDebug("welcome to use sheneninfo release manager system\n\n"
                 "usage: \nreleasemgr --version \t print main system version number\n"
                 "releasemgr --help \t print help document\n");
}

QCommandLineParser* CommandRunner::getCmdParserByCmdName(CommandName cmdName)
{
   QCommandLineParser* parser = nullptr;
   switch(cmdName){
   case CommandName::Fhzc_Build:
   {
      parser = m_optionPool.getFhzcCmdParser();
      break;
   }
   default:
      break;
   }
   return parser;
}

CommandRunner::~CommandRunner()
{
}

}//releasemgr