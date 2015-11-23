#include "global_version_command.h"
#include "io/terminal.h"
namespace releasemgr 
{

GlobalVersionCommand::GlobalVersionCommand(CommandRunner *runner, const CommandMeta &invokeMeta)
   : AbstractCommand(runner, invokeMeta)
{
}

void GlobalVersionCommand::exec()
{
   printConsoleMsg("releasemgr version ");
   printConsoleMsg("v0.0.1-rc1\n", TerminalColor::Cyan);
   exit(EXIT_SUCCESS);
}

GlobalVersionCommand::~GlobalVersionCommand()
{}

}//relasemgr