#ifndef SETTING_H
#define SETTING_H
#include "global/global.h"
QT_BEGIN_NAMESPACE
class QSettings;
class QString;
QT_END_NAMESPACE

namespace releasemgr 
{

class Settings
{
public:
   Settings();
   ~Settings();
   static QString getCfgDir() const;
private:
   QSettings* const m_setings;
};

}//releasemgr

#endif // SETTING_H
