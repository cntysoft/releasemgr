#include "command_meta.h"
#include "command_category.h"
namespace releasemgr
{

CommandMeta::CommandMeta(CommandCategory commandCategory, CommandName commandName, const CmdArgType& args)
   : commandCategory(commandCategory), command(commandName), args(args)
{
   
}

CommandName CommandMeta::getCommandName() const
{
   return command;
}

CommandCategory CommandMeta::getCommandCategory()const
{
   return commandCategory;
}

const CommandMeta::CmdArgType& CommandMeta::getCmdArgs()const
{
   return args;
}

}//releasemgr
