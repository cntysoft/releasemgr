#include <QTimer>
#include <QDebug>
#include <QMap>
#include <QLatin1String>

#include "global/const.h"
#include "global/global.h"
#include "application.h"
#include "io/terminal.h"
#include "kernel/errorinfo.h"
#include "parser/command_runner.h"
#include "global/common_funcs.h"
#include "settings.h"
#include "utils/env_detecter.h"

using namespace std;
using namespace releasemgr;

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
         qDebug() << str;
      }
      return EXIT_FAILURE;
   }
}
