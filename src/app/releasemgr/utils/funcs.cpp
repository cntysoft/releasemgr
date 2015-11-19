#include "funcs.h"
#include "settings.h"
#include "global/common_funcs.h"
#include "application.h"

namespace releasemgr 
{

const Settings& get_sys_settings()
{
   return Application::instance()->getSettings();
}

const Application& get_app_ref()
{
   return *Application::instance();
}

}//releasemgr