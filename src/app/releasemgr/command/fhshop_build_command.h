#ifndef COMMAND_FHSHOP_BUILD_COMMAND_H
#define COMMAND_FHSHOP_BUILD_COMMAND_H

#include "abstract_command.h"
#include "global/global.h"

namespace releasemgr 
{

class AbstractTaskMgr;

class FhshopBuildCommand : public AbstractCommand
{
public:
   FhshopBuildCommand(CommandRunner* runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~FhshopBuildCommand(); 
private:
   AbstractTaskMgr* getTaskMgr();
};

}//releasemgr

#endif // COMMAND_FHSHOP_BUILD_COMMAND_H
