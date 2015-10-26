#include <iostream>
#include "global/global.h"
#include "application.h"
using namespace std;
using namespace releasemgr;

int main(int argc, char *argv[])
{
   Application app(argc, argv);
   return app.exec();
}

