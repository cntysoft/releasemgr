#ifndef RELEASEMGR_COMMAND_GLOBAL_HELP_H
#define RELEASEMGR_COMMAND_GLOBAL_HELP_H

#include "command/abstract_command.h"
#include "command/command_meta.h"
#include "command_runner.h"
namespace releasemgr{
namespace command{

using sn::corelib::AbstractCommand;
using sn::corelib::CommandMeta;
using releasemgr::CommandRunner;

class GlobalHelpCommand : public AbstractCommand
{
public:
   GlobalHelpCommand(CommandRunner& runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~GlobalHelpCommand(); 
};

}//command
}//releasemgr


#endif // RELEASEMGR_COMMAND_GLOBAL_HELP_H
