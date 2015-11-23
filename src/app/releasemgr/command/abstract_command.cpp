#include "abstract_command.h"
#include "utils/funcs.h"
#include "application.h"
#include "settings.h"

namespace releasemgr 
{

AbstractCommand::AbstractCommand(CommandRunner* runner, const CommandMeta& invokeMeta)
   : m_cmdRunner(runner), m_invokeMeta(invokeMeta)
{
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