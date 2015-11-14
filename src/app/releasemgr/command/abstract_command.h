#ifndef ABSTRACT_Command
#define ABSTRACT_Command

#include "global/global.h"
#include "io/terminal.h"

namespace releasemgr
{

class CommandRunner;

class AbstractCommand
{
public:
   virtual void exec() = 0;
   virtual ~AbstractCommand();
   void exit(int exitCode = 0) const;
   void setCommandRunner(CommandRunner* runner);
   void printConsoleMsg(const char* str, TerminalColor color = TerminalColor::Default, bool underline = false, bool blink = false) const;
protected:
   CommandRunner* cmdRunner;
};

}//releasemgr

#endif // ABSTRACT_Command