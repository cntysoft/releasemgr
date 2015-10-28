#ifndef COMMAND_RUNNER
#define COMMAND_RUNNER

#include "global/global.h"

QT_BEGIN_NAMESPACE
class QCommandParser;
QT_END_NAMESPACE

namespace releasemgr
{
class Application;

class CommandRunner
{
public:
   CommandRunner(const Application &app);
   ~CommandRunner();
   void run();
private:
   QCommandParser *cmdParser;
   Application app;
};

}//releasemgr


#endif // COMMAND_RUNNER

