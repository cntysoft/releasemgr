#ifndef Command_RUNNER
#define Command_RUNNER

#include "global/global.h"
#include "option_pool.h"
#include "command/command_meta.h"
#include "command/command_category.h"
#include <QStringList>

QT_BEGIN_NAMESPACE
class QCommandLineParser;
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
   QCommandLineParser* getCmdParserByType(const char* type);
   QStringList getSupportSubCommands() const;
   void runCmd(const CommandMeta& meta);
private:
   OptionPool optionPool;
   const Application &app;
   static const CmdPoolType cmdRegisterPool;
};

}//releasemgr

#endif // Command_RUNNER
