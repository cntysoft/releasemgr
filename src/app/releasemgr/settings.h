#ifndef SETTING_H
#define SETTING_H

#include <QSettings>
#include <QVariant>

#include "global/global.h"
#include "const.h"

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

namespace releasemgr 
{

class Settings
{
public:
   using Status = QSettings::Status;
public:
   Settings();
   ~Settings();
   static const QString& getCfgDir();
   static const QString& getCfgFilename();
   void sync();
   Status getStatus() const;
   QVariant getValue(const QString& key, const QString& group = CFG_GROUP_GLOABL, const QVariant & defaultValue = QVariant()) const;
   void setValue(const QString& key, const QVariant& value, const QString& group = CFG_GROUP_GLOABL);
   QStringList getChildKeys(const QString& path = QString());
private:
   QSettings* createQSettings();
   void initDefaultConf();
   friend void init_defualt_cfg(Settings& Settings);
   int enterGroup(const QString& path);
   void exitGroup(int depth);
private:  
   QSettings* const m_settings;
};

}//releasemgr

#endif // SETTING_H
