#ifndef RMMGR_UTILS_FUNCS_H
#define RMMGR_UTILS_FUNCS_H

namespace releasemgr 
{

class Settings;
class Application;

const Settings& get_sys_settings();
const Application& get_app_ref();

}//releasemgr

#endif // RMMGR_UTILS_FUNCS_H
