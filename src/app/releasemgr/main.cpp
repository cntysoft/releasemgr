#include "global/global.h"
#include "application.h"
#include "parser/command_runner.h"

using namespace std;
using namespace releasemgr;

int main(int argc, char *argv[])
{
   Application app(argc, argv);
//   CommandRunner cmdrunner(app);
//   cmdrunner.run();
   return app.exec();
}

