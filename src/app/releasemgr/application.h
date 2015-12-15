#ifndef RELEASEMGR_APPLICATION_H
#define RELEASEMGR_APPLICATION_H

#include "kernel/application.h"
#include "kernel/settings.h"

namespace releasemgr
{

using BaseApplication = sn::corelib::Application;
using sn::corelib::Settings;

class Application : public BaseApplication
{
public:
   Application(int &argc, char **argv);
public:
   virtual Settings::CfgInitializerFnType getDefaultCfgInitializerFn();
   virtual ~Application();
};

}//releasemgr

#endif // RELEASEMGR_APPLICATION_H
