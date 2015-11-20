#include <QString>
#include <QSettings>
#include <QFile>
#include <QLatin1Char>

#include "settings.h"
#include "global/common_funcs.h"
#include "const.h"


namespace releasemgr 
{

Settings::Settings()
   :m_settings(createQSettings())
{
   QFile cfgFilename(getCfgFilename());
//   if(!cfgFilename.exists()){
//      initDefaultConf();
//   }
   initDefaultConf();
}

const QString& Settings::getCfgDir()
{
   static QString cfgDir(get_current_user_home_dir() + "/.config/sheneninfo/releasemgr");
   return cfgDir;
}

const QString& Settings::getCfgFilename()
{
   static QString cfgFilename(getCfgDir() + '/' + CFG_FILE_NAME);
   return cfgFilename;
}

QSettings* Settings::createQSettings()
{
   return new QSettings(getCfgFilename(), QSettings::Format::NativeFormat);
}

void Settings::initDefaultConf()
{
   init_defualt_cfg(*this);
}


Settings::Status Settings::getStatus()const
{
   return m_settings->status();
}

QVariant Settings::getValue(const QString &key, const QString &group, const QVariant &defaultValue) const
{
   m_settings->beginGroup(group);
   QVariant value = m_settings->value(key, defaultValue);
   m_settings->endGroup();
   return value;
}

void Settings::setValue(const QString &key, const QVariant &value, const QString &group)
{
   m_settings->beginGroup(group);
   m_settings->setValue(key,value);
   m_settings->endGroup();
}

void Settings::sync()
{
   m_settings->sync();
}

Settings::~Settings()
{
   delete m_settings;
}

}//releasemgr