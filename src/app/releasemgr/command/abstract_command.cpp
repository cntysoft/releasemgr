#include "abstract_command.h"
#include "global/common_funcs.h"
#include <QCoreApplication>
#include "parser/command_runner.h"
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
   QCoreApplication* app = get_core_application();
   app->exit(exitCode);
}

void AbstractCommand::printConsoleMsg(const char *str, TerminalColor color, bool underline, bool blink) const
{
   Terminal::writeText(str, color, underline, blink);
}

}//relasemgr