#include "command_meta.h"

namespace releasemgr
{

CommandMeta::CommandMeta(CommandType cmdType, const QMap<QLatin1String, QString> args)
   : commandType(cmdType), args(args)
{
   
}

CommandType CommandMeta::getCommandType()const
{
   return commandType;
}

const QMap<QLatin1String, QString>& CommandMeta::getCmdArgs()const
{
   return args;
}

}//releasemgr