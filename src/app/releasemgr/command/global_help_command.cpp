#include "global_help_command.h"

namespace releasemgr 
{
   
void GlobalHelpCommand::exec()
{
   cmdRunner->printUsage();
   exit(EXIT_SUCCESS);
}

GlobalHelpCommand::~GlobalHelpCommand()
{}

}//releasemgr