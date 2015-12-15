#ifndef RMMGR_UTILS_FUNCS_H
#define RMMGR_UTILS_FUNCS_H

#include "kernel/settings.h"

namespace releasemgr 
{

using sn::corelib::Settings;

class Application;

const Settings& get_sys_settings();

}//releasemgr

#endif // RMMGR_UTILS_FUNCS_H
