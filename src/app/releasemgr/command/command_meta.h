#ifndef Command_META_H
#define Command_META_H

#include <QMap>
#include <QString>

namespace releasemgr
{
enum class CommandCategory;
enum class CommandName;

class CommandMeta
{
public:
   using CmdArgType = QMap<QString, QString>;
   CommandMeta(CommandCategory category, CommandName commandName, const CmdArgType& args);
   CommandCategory getCommandCategory()const;
   CommandName getCommandName()const;
   const CmdArgType& getCmdArgs()const;
private:
   CommandCategory commandCategory;
   CommandName command;
   CmdArgType args;
};

}//releasemgr

#endif // Command_META_H

