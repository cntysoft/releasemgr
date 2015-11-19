#ifndef FUNCS_H
#define FUNCS_H

namespace releasemgr 
{

class Settings;
class Application;

const Settings& get_sys_settings();
const Application& get_app_ref();

}//releasemgr

#endif // FUNCS_H
