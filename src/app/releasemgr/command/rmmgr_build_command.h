#ifndef RELEASEMGR_COMMAND_RMMGR_BUILD_COMMAND_H
#define RELEASEMGR_COMMAND_RMMGR_BUILD_COMMAND_H

#include "command/abstract_command.h"
#include "command/command_meta.h"
#include "command_runner.h"

namespace releasemgr{
namespace command{

using sn::corelib::AbstractCommand;
using sn::corelib::CommandMeta;
using releasemgr::CommandRunner;

class RmMgrBuildCommand : public AbstractCommand
{
public:
   RmMgrBuildCommand(CommandRunner& runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~RmMgrBuildCommand();
};

}//command
}//releasemgr


#endif // RELEASEMGR_COMMAND_RMMGR_BUILD_COMMAND_H
