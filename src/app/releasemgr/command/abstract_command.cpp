#include "abstract_command.h"
#include "utils/funcs.h"
#include "application.h"

namespace releasemgr 
{

void AbstractCommand::setCommandRunner(CommandRunner *runner)
{
   cmdRunner = runner;
}

AbstractCommand::~AbstractCommand()
{
}

void AbstractCommand::exit(int exitCode) const
{
   const Application& app = get_app_ref();
   app.exit(exitCode);
}

void AbstractCommand::printConsoleMsg(const char *str, TerminalColor color, bool underline, bool blink) const
{
   Terminal::writeText(str, color, underline, blink);
}

}//relasemgr