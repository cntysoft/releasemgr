#ifndef GLOBAL_VERSION_H
#define GLOBAL_VERSION_H

#include "command/abstract_command.h"

namespace releasemgr 
{

class GlobalVersionCommand : public AbstractCommand
{
public:
   virtual void exec();
   virtual ~GlobalVersionCommand();
};

}//releasemgr

#endif // GLOBAL_VERSION_H
