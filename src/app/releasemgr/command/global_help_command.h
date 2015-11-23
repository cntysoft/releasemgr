#ifndef GLOBAL_HELP_H
#define GLOBAL_HELP_H
#include "command/abstract_command.h"

namespace releasemgr 
{

class GlobalHelpCommand : public AbstractCommand
{
public:
   GlobalHelpCommand(CommandRunner* runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~GlobalHelpCommand(); 
};

}//releasemgr


#endif // GLOBAL_HELP_H
