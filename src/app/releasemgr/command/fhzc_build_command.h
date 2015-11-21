#ifndef FHZC_FULL_BUILD_COMMAND_H
#define FHZC_FULL_BUILD_COMMAND_H

#include "abstract_command.h"

namespace releasemgr 
{

class FhzcBuildCommand : public AbstractCommand
{
public:
   virtual void exec();
   virtual ~FhzcBuildCommand();  
};

}//releasemgr

#endif // FHZC_FULL_BUILD_COMMAND_H
