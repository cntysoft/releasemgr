#ifndef Command_TYPE_H
#define Command_TYPE_H

namespace releasemgr
{

enum class CommandCategory
{
   Global,
   DeployServer,
   Fhzc,
   Fhshop,
   Unknow
};

enum class CommandName
{
   Unknow,
   Global_Version,
   Global_Help,
   Fhzc_Build,
   Fhzc_DiffBuild,
   Fhzc_DocBuild
   
};

}//releasemgr

#endif // Command_TYPE_H