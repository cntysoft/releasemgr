#include "global_help_command.h"

namespace releasemgr 
{
   
GlobalHelpCommand::GlobalHelpCommand(CommandRunner *runner, const CommandMeta &invokeMeta)
   : AbstractCommand(runner, invokeMeta)
{}

void GlobalHelpCommand::exec()
{
   m_cmdRunner->printUsage();
   exit(EXIT_SUCCESS);
}

GlobalHelpCommand::~GlobalHelpCommand()
{}

}//releasemgr