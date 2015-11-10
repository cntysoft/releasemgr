#ifndef COMMON_FUNCS_H
#define COMMON_FUNCS_H
#include "global.h"

QT_BEGIN_NAMESPACE
class QCoreApplication;
QT_END_NAMESPACE

namespace releasemgr
{

RMGR_EXPORT QCoreApplication* get_core_application();

}//releasemgr

#endif // COMMON_FUNCS_H