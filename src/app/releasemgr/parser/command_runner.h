#ifndef Command_RUNNER
#define Command_RUNNER

#include "global/global.h"
#include "option_pool.h"
#include "Command/Command_meta.h"
#include <QStringList>

QT_BEGIN_NAMESPACE
class QCommandLineParser;
QT_END_NAMESPACE

namespace releasemgr
{

class Application;

class CommandRunner
{
   Q_DISABLE_COPY(CommandRunner)
public:
   CommandRunner(const Application &app);
   void printUsage()const;
   ~CommandRunner();
   void run();
protected:
   QCommandLineParser* getCmdParserByType(const char* type);
   QStringList getSupportSubCommands() const;
   void runCmd(const CommandMeta& meta);
private:
   OptionPool optionPool;
   const Application &app;
};

}//releasemgr

#endif // Command_RUNNER
