#include "common_funcs.h"
#include <QCoreApplication>
#include <QString>
#include <pwd.h>
#include <unistd.h>

namespace releasemgr 
{

QCoreApplication* get_core_application()
{
   return QCoreApplication::instance();
}

QString get_current_user_home_dir()
{
   passwd* pwd = getpwuid(getuid());
   return QString(pwd->pw_dir);
}

}//releasemgr