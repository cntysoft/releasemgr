#include <QTimer>
#include <QDebug>
#include "global/global.h"
#include "application.h"
#include "io/terminal.h"
#include "kernel/errorinfo.h"
#include "parser/command_runner.h"
#include <QMap>
#include <QLatin1String>
#include "global/const.h"
using namespace std;
using namespace releasemgr;

int main(int argc, char *argv[])
{
   try{
      Application app(argc, argv);
      CommandRunner cmdrunner(app);
      QTimer::singleShot(0, Qt::PreciseTimer, [&cmdrunner]{
         cmdrunner.run();
      });
      return app.exec();
   }catch(const ErrorInfo& errorInfo){
      qDebug() << errorInfo.toString();
      return EXIT_FAILURE;
   }
}