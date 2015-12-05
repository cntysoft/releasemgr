#ifndef COMMAND_FHZC_FULL_BUILD_COMMAND_H
#define COMMAND_FHZC_FULL_BUILD_COMMAND_H

#include "abstract_command.h"
#include "global/global.h"

namespace releasemgr 
{

class AbstractTaskMgr;

class FhzcBuildCommand : public AbstractCommand
{
public:
   FhzcBuildCommand(CommandRunner* runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~FhzcBuildCommand(); 
private:
   AbstractTaskMgr* getTaskMgr();
};

}//releasemgr

#endif // COMMAND_FHZC_FULL_BUILD_COMMAND_H
