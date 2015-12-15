#include "application.h"
#include "kernel/settings.h"

namespace releasemgr 
{

using sn::corelib::Settings;

extern void init_defualt_cfg(Settings &settings);

Application::Application(int &argc, char **argv)
   : BaseApplication(argc, argv)
{
   setApplicationName("releasemgr");
}

Settings::CfgInitializerFnType Application::getDefaultCfgInitializerFn()
{
   return init_defualt_cfg;
}

Application::~Application()
{}

}//releasemgr