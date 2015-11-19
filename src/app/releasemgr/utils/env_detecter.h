#ifndef ENV_DETECTER_H
#define ENV_DETECTER_H

#include <QMap>
#include <QLatin1String>

namespace releasemgr 
{

class Settings;

class EnvDetecter
{
public:
   const char* IS_DETECT_KEY = "env_detected";
   using EnvProgramType = QMap<QLatin1String, QLatin1String>;
public:
   EnvDetecter(const Settings& settings);
   void detect() const;
private:
   bool isNeedDetect() const;
private:
   const Settings& m_settings;
   const static EnvProgramType envDetectRepo;
};

}//releasemgr

#endif // ENV_DETECTER_H
