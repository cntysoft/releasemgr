#include <QTimer>
#include <QMap>
#include <QLatin1String>

#include "global/global.h"
#include "application.h"
#include "io/terminal.h"
#include "kernel/errorinfo.h"
#include "command_runner.h"
#include "global/common_funcs.h"
#include "utils/env_detecter.h"
#include "io/terminal.h"

using releasemgr::CommandRunner;
using releasemgr::EnvDetecter;
using releasemgr::Application;
using sn::corelib::Terminal;
using sn::corelib::TerminalColor;
using sn::corelib::ErrorInfo;

int main(int argc, char *argv[])
{
   try{
      Application app(argc, argv);
      //探测服务器环境，一般只会运行一次
      EnvDetecter envDetecter(app.getSettings());
      envDetecter.detect();
      CommandRunner cmdrunner(app);
      QTimer::singleShot(0, Qt::PreciseTimer, [&cmdrunner]{
         cmdrunner.run();
      });
      return app.exec();
   }catch(const ErrorInfo& errorInfo){
      QString str(errorInfo.toString());
      if(str.size() > 0){
         str += '\n';
         Terminal::writeText(str.toLatin1(), TerminalColor::Red);
      }
      return EXIT_FAILURE;
   }
}
