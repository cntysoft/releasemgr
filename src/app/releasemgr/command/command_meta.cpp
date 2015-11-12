#include "command_meta.h"

namespace releasemgr
{

CommandMeta::CommandMeta(CommandCategory commandCategory, CommandName commandName, const QMap<QLatin1String, QString>& args)
   : commandCategory(commandCategory), commandName(commandName), args(args)
{
   
}

CommandCategory CommandMeta::getCommandCategory()const
{
   return CommandCategory;
}

const QMap<QLatin1String, QString>& CommandMeta::getCmdArgs()const
{
   return args;
}

}//releasemgr