#include "funcs.h"
#include "global/common_funcs.h"
#include "application.h"

namespace releasemgr 
{

const Settings& get_sys_settings()
{
   return Application::instance()->getSettings();
}


}//releasemgr