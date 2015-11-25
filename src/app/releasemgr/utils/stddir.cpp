#include <QDir>

#include "stddir.h"

namespace releasemgr 
{

const QString& StdDir::getAssetsDir()
{
   static QString assetDir(StdDir::getShareResDir() + QDir::separator() + "assets");
   return assetDir;
}

const QString& StdDir::getShareResDir()
{
   static QString shareResDir(RMGR_SHARE_RES_DIR);
   return shareResDir;
}

}//releasemgr