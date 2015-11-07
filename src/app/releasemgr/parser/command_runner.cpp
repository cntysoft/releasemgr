#include "command_runner.h"
#include "../application.h"
#include "kernel/errorinfo.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>  
namespace releasemgr
{

CommandRunner::CommandRunner(const Application &app)
   :app(app)
{
   setupCmdParser();
}

void CommandRunner::run() const
{
   
}

void CommandRunner::setupCmdParser()
{
   
}
CommandRunner::~CommandRunner()
{
   
//   delete cmdParser;
}

}//releasemgr