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
   if(!cfgFilename.exists()){
      initDefaultConf();
   }
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

QString Settings::internalKeyRepresentation(const QString &key) const
{
   QString internalKey = key;
   return internalKey.replace(QLatin1Char('.'), QLatin1Char('/'));
}

QString Settings::externalKeyRepresentation(const QString &key) const
{
   QString externalKey = key;
   return externalKey.replace(QLatin1Char('/'), QLatin1Char('.'));
}

Settings::Status Settings::getStatus()const
{
   return m_settings->status();
}

QVariant Settings::getValue(const QString &key, const QString &group, const QVariant &defaultValue) const
{
   m_settings->beginGroup(internalKeyRepresentation(group));
   QVariant value = m_settings->value(internalKeyRepresentation(key), defaultValue);
   m_settings->endGroup();
   return value;
}

void Settings::setValue(const QString &key, const QVariant &value, const QString &group)
{
   m_settings->beginGroup(internalKeyRepresentation(group));
   m_settings->setValue(internalKeyRepresentation(key),value);
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