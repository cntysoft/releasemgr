#ifndef COMMAND_RUNNER
#define COMMAND_RUNNER

#include "global/global.h"
#include "option_pool.h"
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
   void run() const;
protected:
   QCommandLineParser& getCmdParserByType(const char* type);
   QStringList getSupportSubCommands() const;
private:
   OptionPool optionPool;
   const Application &app;
};

}//releasemgr

#endif // COMMAND_RUNNER
