#ifndef COMMAND_RMMGR_BUILD_COMMAND_H
#define COMMAND_RMMGR_BUILD_COMMAND_H

#include "command/abstract_command.h"

namespace releasemgr 
{

class RmMgrBuildCommand : public AbstractCommand
{
public:
   RmMgrBuildCommand(CommandRunner* runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~RmMgrBuildCommand();
};

}//releasemgr


#endif // COMMAND_RMMGR_BUILD_COMMAND_H
