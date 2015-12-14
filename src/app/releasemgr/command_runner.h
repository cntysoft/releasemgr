#ifndef RELEASEMGR_COMMAND_RUNNER
#define RELEASEMGR_COMMAND_RUNNER

#include "command/abstract_command_runner.h"

namespace releasemgr 
{

using BaseCommandRunner = sn::corelib::AbstractCommandRunner;

class Application;

class CommandRunner : public BaseCommandRunner
{
public:
   CommandRunner(Application &app);
private:
   void initCommandPool();
   void initRouteItems();
};


}//releasemgr

#endif // RELEASEMGR_COMMAND_RUNNER

