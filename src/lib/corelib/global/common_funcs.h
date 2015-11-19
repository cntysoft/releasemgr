#ifndef COMMON_FUNCS_H
#define COMMON_FUNCS_H
#include "global.h"

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

namespace releasemgr
{

RMGR_EXPORT QString get_current_user_home_dir();

}//releasemgr

#endif // COMMON_FUNCS_H