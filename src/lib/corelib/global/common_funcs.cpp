#include "common_funcs.h"
#include <QCoreApplication>
namespace releasemgr 
{

QCoreApplication* get_core_application()
{
   return QCoreApplication::instance();
}

}//releasemgr