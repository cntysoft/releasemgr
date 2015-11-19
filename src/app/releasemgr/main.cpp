#include <QTimer>
#include <QDebug>
#include <QMap>
#include <QLatin1String>

#include "const.h"
#include "global/const.h"
#include "global/global.h"
#include "application.h"
#include "io/terminal.h"
#include "kernel/errorinfo.h"
#include "parser/command_runner.h"
#include "global/common_funcs.h"

using namespace std;
using namespace releasemgr;

int main(int argc, char *argv[])
{
   try{
      Application app(argc, argv);
      CommandRunner cmdrunner(app);
      QTimer::singleShot(0, Qt::PreciseTimer, [&cmdrunner]{
         qDebug() << get_current_user_home_dir();
         cmdrunner.run();
      });
      return app.exec();
   }catch(const ErrorInfo& errorInfo){
      qDebug() << errorInfo.toString();
      return EXIT_FAILURE;
   }
}
