#ifndef COMMAND_META_H
#define COMMAND_META_H

#include <QMap>
#include <QLatin1String>
#include <QString>

namespace releasemgr
{
enum class CommandType;

class CommandMeta
{
public:
   CommandMeta(CommandType cmdType, const QMap<QLatin1String, QString> args);
   inline CommandType getCommandType()const;
   inline const QMap<QLatin1String, QString>& getCmdArgs()const;
private:
   CommandType commandType;
   QMap<QLatin1String, QString> args;
};

}//releasemgr

#endif // COMMAND_META_H

