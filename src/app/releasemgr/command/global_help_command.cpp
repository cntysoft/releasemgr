#include "global_help_command.h"
#include "command_runner.h"

namespace releasemgr{
namespace command{

GlobalHelpCommand::GlobalHelpCommand(CommandRunner& runner, const CommandMeta& invokeMeta)
   : AbstractCommand(runner, invokeMeta)
{}

void GlobalHelpCommand::exec()
{
   m_cmdRunner.printUsage();
   exit(EXIT_SUCCESS);
}

GlobalHelpCommand::~GlobalHelpCommand()
{}
}//command
}//releasemgr