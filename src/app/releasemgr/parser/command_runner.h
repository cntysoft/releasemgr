#ifndef COMMAND_RUNNER
#define COMMAND_RUNNER

#include "global/global.h"
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
   QString getUsage()const;
   ~CommandRunner();
 
   void run() const;
private:
   OptionPool optionPool;
   const Application &app;
};

}//releasemgr

#endif // COMMAND_RUNNER
