#ifndef RELEASEMGR_COMMAND_FHZC_FULL_BUILD_COMMAND_H
#define RELEASEMGR_COMMAND_FHZC_FULL_BUILD_COMMAND_H

#include "command/abstract_command.h"
#include "global/global.h"
#include "command/command_meta.h"
#include "command_runner.h"
#include "task/abstract_taskmgr.h"

namespace releasemgr{
namespace command{

using sn::corelib::AbstractCommand;
using sn::corelib::CommandMeta;
using releasemgr::CommandRunner;
using releasemgr::AbstractTaskMgr;

class FhzcBuildCommand : public AbstractCommand
{
public:
   FhzcBuildCommand(CommandRunner& runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~FhzcBuildCommand(); 
private:
   AbstractTaskMgr* getTaskMgr();
};

}//command
}//releasemgr

#endif // RELEASEMGR_COMMAND_FHZC_FULL_BUILD_COMMAND_H
