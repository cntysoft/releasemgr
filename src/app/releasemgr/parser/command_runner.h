#ifndef Command_RUNNER
#define Command_RUNNER

#include <QList>

#include "global/global.h"
#include "option_pool.h"
#include "command/command_meta.h"
#include "command/command_category.h"

QT_BEGIN_NAMESPACE
class QCommandLineParser;
class QString;
QT_END_NAMESPACE

namespace releasemgr
{

class Application;
class AbstractCommand;
class Settings;

class CommandRunner
{
   Q_DISABLE_COPY(CommandRunner)
public:
   CommandRunner(Application &app);
   void printUsage()const;
   Settings& getSysSettings();
   ~CommandRunner();
   void run();
protected:
   using CmdPoolType = QMap<CommandName, AbstractCommand* (*)(CommandRunner*, const CommandMeta& meta)>;
   using CmdNameRepoType = QMap<QString, CommandName>;
   QCommandLineParser* getCmdParserByCmdName(CommandName cmdName);
   QList<QString> getSupportSubCommands() const;
   void runCmd(const CommandMeta& meta);
   bool isSubCmdSupported(const QString& cmd) const;
private:
   CommandMeta::CmdArgType parseSubCmdArgs(CommandCategory& category, CommandName cmd, const QStringList& invokeArgs);
   void parseFhzcFullBuildCmdArgs(const QStringList& invokeArgs, CommandMeta::CmdArgType& args);
private:
   OptionPool m_optionPool;
   Application& m_app;
   static const CmdPoolType m_cmdRegisterPool;
   static const CmdNameRepoType m_subCmdNameMap;
};

}//releasemgr

#endif // Command_RUNNER
