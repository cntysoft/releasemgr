#ifndef FHZC_FULL_BUILD_COMMAND_H
#define FHZC_FULL_BUILD_COMMAND_H

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

#endif // FHZC_FULL_BUILD_COMMAND_H
