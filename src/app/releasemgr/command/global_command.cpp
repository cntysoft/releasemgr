#include <QString>

#include "global_command.h"
#include "command_runner.h"

#include "corelib/io/terminal.h"

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

using sn::corelib::TerminalColor;

GlobalVersionCommand::GlobalVersionCommand(CommandRunner& runner, const CommandMeta& invokeMeta)
   : AbstractCommand(runner, invokeMeta)
{
}

void GlobalVersionCommand::exec()
{
   printConsoleMsg("releasemgr version ");
   printConsoleMsg(QString("%1\n").arg(RMMGR_VERSION), TerminalColor::Cyan);
   exit(EXIT_SUCCESS);
}

GlobalVersionCommand::~GlobalVersionCommand()
{}


}//command
}//releasemgr