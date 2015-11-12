#ifndef Command_META_H
#define Command_META_H

#include <QMap>
#include <QLatin1String>
#include <QString>

namespace releasemgr
{
enum class CommandCategory;
enum class CommandName;

class CommandMeta
{
public:
   CommandMeta(CommandCategory category, CommandName commandName, const QMap<QLatin1String, QString>& args);
   inline CommandCategory getCommandCategory()const;
   inline CommandName getCommandName()const;
   inline const QMap<QLatin1String, QString>& getCmdArgs()const;
private:
   CommandCategory CommandCategory;
   CommandName Command;
   QMap<QLatin1String, QString> args;
   
};

}//releasemgr

#endif // Command_META_H

