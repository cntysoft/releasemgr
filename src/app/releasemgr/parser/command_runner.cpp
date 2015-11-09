#include "command_runner.h"
#include "application.h"
#include "kernel/errorinfo.h"
#include <QCommandLineParser>

namespace releasemgr
{

CommandRunner::CommandRunner(const Application &app)
   :app(app)
{
}

void CommandRunner::run() const
{
   
}

CommandRunner::~CommandRunner()
{
}

}//releasemgr
