#ifndef RELEASEMGR_COMMAND_BUILD_COMMAND_H
#define RELEASEMGR_COMMAND_BUILD_COMMAND_H

#include "command/abstract_command.h"
#include "command/command_meta.h"
#include "command_runner.h"

namespace releasemgr{
namespace command{

using sn::corelib::AbstractCommand;
using sn::corelib::CommandMeta;
using releasemgr::CommandRunner;

class CloudControllerBuildCommand : public AbstractCommand
{
public:
   CloudControllerBuildCommand(CommandRunner& runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~CloudControllerBuildCommand();
};


class DeploySystemBuildCommand : public AbstractCommand
{
public:
   DeploySystemBuildCommand(CommandRunner& runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~DeploySystemBuildCommand();
};

class RmMgrBuildCommand : public AbstractCommand
{
public:
   RmMgrBuildCommand(CommandRunner& runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~RmMgrBuildCommand();
};

class UpgrademgrBuildCommand : public AbstractCommand
{
public:
   UpgrademgrBuildCommand(CommandRunner& runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~UpgrademgrBuildCommand();
};

class ZhuChaoBuildCommand : public AbstractCommand
{
public:
   ZhuChaoBuildCommand(CommandRunner& runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~ZhuChaoBuildCommand();
};

class UpgradeTesterBuildCommand : public AbstractCommand
{
public:
   UpgradeTesterBuildCommand(CommandRunner& runner, const CommandMeta& invokeMeta);
public:
   virtual void exec();
   virtual ~UpgradeTesterBuildCommand();
};

}//command
}//releasemgr

#endif // RELEASEMGR_COMMAND_BUILD_COMMAND_H
