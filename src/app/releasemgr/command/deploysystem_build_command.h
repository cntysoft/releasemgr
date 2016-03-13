#ifndef RELEASEMGR_COMMAND_DEPLOYSYSTEM_BUILD_COMMAND_H
#define RELEASEMGR_COMMAND_DEPLOYSYSTEM_BUILD_COMMAND_H

#include "command/abstract_command.h"
#include "command/command_meta.h"
#include "command_runner.h"

namespace releasemgr{
namespace command{

using sn::corelib::AbstractCommand;
using sn::corelib::CommandMeta;
using releasemgr::CommandRunner;

class DeploySystemBuildCommand : public AbstractCommand
{
public:
   DeploySystemBuildCommand(CommandRunner& runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~DeploySystemBuildCommand();
};

}//command
}//releasemgr


#endif // RELEASEMGR_COMMAND_DEPLOYSYSTEM_BUILD_COMMAND_H
