#ifndef RELEASEMGR_COMMAND_FHSHOP_BUILD_COMMAND_H
#define RELEASEMGR_COMMAND_FHSHOP_BUILD_COMMAND_H

#include "command/abstract_command.h"
#include "global/global.h"
#include "task/abstract_taskmgr.h"
#include "command_runner.h"

namespace releasemgr{
namespace command{

using sn::corelib::AbstractCommand;
using sn::corelib::CommandMeta;
using releasemgr::AbstractTaskMgr;

class FhshopBuildCommand : public AbstractCommand
{
public:
   FhshopBuildCommand(CommandRunner& runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~FhshopBuildCommand(); 
private:
   AbstractTaskMgr* getTaskMgr();
};

}//command
}//releasemgr

#endif // RELEASEMGR_COMMAND_FHSHOP_BUILD_COMMAND_H
