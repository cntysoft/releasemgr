#ifndef ABSTRACT_Command
#define ABSTRACT_Command

#include "global/global.h"
#include "io/terminal.h"
#include "parser/command_runner.h"
namespace releasemgr
{

using sn::corelib::Terminal;
using sn::corelib::TerminalColor;

class AbstractCommand
{
   Q_DISABLE_COPY(AbstractCommand)
public:
   AbstractCommand(CommandRunner* runner, const CommandMeta& invokeMeta);
   void exit(int exitCode = 0) const;
   void printConsoleMsg(const char* str, TerminalColor color = TerminalColor::Default, bool underline = false, bool blink = false) const;
public:
   virtual void exec() = 0;
   virtual ~AbstractCommand();
protected:
   CommandRunner* const m_cmdRunner;
   CommandMeta m_invokeMeta;
};

}//releasemgr

#endif // ABSTRACT_Command