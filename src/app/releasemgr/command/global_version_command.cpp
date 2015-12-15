#include <QString>

#include "global_version_command.h"
#include "io/terminal.h"

namespace releasemgr{
namespace command{

using sn::corelib::TerminalColor;

GlobalVersionCommand::GlobalVersionCommand(CommandRunner& runner, const CommandMeta& invokeMeta)
   : AbstractCommand(runner, invokeMeta)
{
}

void GlobalVersionCommand::exec()
{
   printConsoleMsg("releasemgr version ");
   printConsoleMsg(QString("%1\n").arg(RMMGR_VERSION).toLocal8Bit(), TerminalColor::Cyan);
   exit(EXIT_SUCCESS);
}

GlobalVersionCommand::~GlobalVersionCommand()
{}

}//command
}//relasemgr