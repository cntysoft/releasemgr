#ifndef RELEASEMGR_UTILS_STDDIR_H
#define RELEASEMGR_UTILS_STDDIR_H

#include "global/global.h"

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

namespace releasemgr 
{

class StdDir
{
public:
   static const QString& getShareResDir();
   static const QString& getAssetsDir();
};

}//releasemgr

#endif // RELEASEMGR_UTILS_STDDIR_H
