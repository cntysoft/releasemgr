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

class CommandRunner
{
   Q_DISABLE_COPY(CommandRunner)
public:
   CommandRunner(const Application &app);
   void printUsage()const;
   ~CommandRunner();
   void run();
protected:
   using CmdPoolType = QMap<CommandName, AbstractCommand* (*)(CommandRunner*)>;
   using CmdNameRepoType = QMap<QString, CommandName>;
   QCommandLineParser* getCmdParserByCmdName(CommandName cmdName);
   QList<QString> getSupportSubCommands() const;
   void runCmd(const CommandMeta& meta);
   bool isSubCmdSupported(const QString& cmd) const;
   CommandMeta::CmdArgType parseSubCmdArgs(CommandName cmd, const QStringList& invokeArgs);
private:
   OptionPool m_optionPool;
   const Application& m_app;
   static const CmdPoolType m_cmdRegisterPool;
   static const CmdNameRepoType m_subCmdNameMap;
};

}//releasemgr

#endif // Command_RUNNER
