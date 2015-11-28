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
#include "settings.h"

namespace releasemgr
{

CommandRunner::CommandRunner(Application &app)
   :m_app(app)
{
}
const CommandRunner::CmdPoolType CommandRunner::m_cmdRegisterPool{
   {CommandName::Global_Help,[](CommandRunner* runner, const CommandMeta& meta)->AbstractCommand*{
         GlobalHelpCommand* cmd = new GlobalHelpCommand(runner, meta);
         return cmd;
      }},
   {CommandName::Global_Version, [](CommandRunner* runner, const CommandMeta& meta)->AbstractCommand*{
         GlobalVersionCommand* cmd = new GlobalVersionCommand(runner, meta);
         return cmd;
      }},
   {CommandName::Fhzc_Build, [](CommandRunner* runner, const CommandMeta& meta)->AbstractCommand*{
         FhzcBuildCommand* cmd = new FhzcBuildCommand(runner, meta);
         return cmd;
      }}
};

const CommandRunner::CmdNameRepoType CommandRunner::m_subCmdNameMap{
   {"fhzc", CommandName::Fhzc_Build}
};

Settings& CommandRunner::getSysSettings()
{
   return m_app.getSettings();
}

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
      cmdArgs = parseSubCmdArgs(cmdCategory, cmdName, targetArgs);
   }
   runCmd(CommandMeta(cmdCategory, cmdName, cmdArgs));
}

CommandMeta::CmdArgType CommandRunner::parseSubCmdArgs(CommandCategory& category, CommandName command, const QStringList& invokeArgs)
{
   
   CommandMeta::CmdArgType args;
   switch (command) {
   case CommandName::Fhzc_Build:
   {
      parseFhzcBuildCmdArgs(invokeArgs, args);
      category = CommandCategory::Fhzc;
      break;
   }
   default:
      break;
   }
   return args;
}

void CommandRunner::parseFhzcBuildCmdArgs(const QStringList &invokeArgs, CommandMeta::CmdArgType &args)
{
   QCommandLineParser* parser = m_optionPool.getFhzcCmdParser();
   parser->process(invokeArgs);
   OptionPool::OptionMapType opts = m_optionPool.getFhzcOptions();
   QStringList positionArgs = parser->positionalArguments();
   bool syntaxOk = true;
   if(1 != positionArgs.count()){
      syntaxOk = false;
   }
   QString action = positionArgs.takeFirst();
   args[QLatin1String("action")] = action;
   //这里按照action解析命令行参数
   if(action == "fullbuild"){
      QCommandLineOption* versionOpt = opts["version"];
      QString version = parser->value(*versionOpt);
      if(version.isEmpty()){
         syntaxOk = false;
         goto THE_END;
      }
      QCommandLineOption* aliyunOpt = opts["aliyun"];
      if(parser->isSet(*aliyunOpt)){
         args[QLatin1String("aliyun")] = true;
      }else{
         args[QLatin1String("aliyun")] = false;
      }
      args[QLatin1String("version")] = version;
   }else if(action == "diffbuild"){
      QCommandLineOption* fromOpt  = opts["from"];
      QCommandLineOption* toOpt = opts["to"];
      QCommandLineOption* aliyunOpt = opts["aliyun"];
      QString from = parser->value(*fromOpt);
      QString to = parser->value(*toOpt);
      if(from.isEmpty()){
         syntaxOk = false;
         goto THE_END;
      }
      if(to.isEmpty()){
         syntaxOk = false;
         goto THE_END;
      }
      if(parser->isSet(*aliyunOpt)){
         args[QLatin1String("aliyun")] = true;
      }else{
         args[QLatin1String("aliyun")] = false;
      }
      args[QLatin1String("from")] = from;
      args[QLatin1String("to")] = to;
   }else if(action == "docbuild"){
      
   }else{
      syntaxOk = false;
   }
   THE_END:
   if(!syntaxOk){
      printUsage();
      throw ErrorInfo();
   }
}

void CommandRunner::runCmd(const CommandMeta& meta)
{
   AbstractCommand* (*initializer)(CommandRunner*, const CommandMeta&) = m_cmdRegisterPool[meta.getCommandName()];
   QScopedPointer<AbstractCommand> cmd(initializer(this, meta));
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