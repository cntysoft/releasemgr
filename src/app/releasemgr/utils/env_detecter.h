#ifndef RMMGR_UTILS_ENV_DETECTER_H
#define RMMGR_UTILS_ENV_DETECTER_H

#include <QStringList>

namespace releasemgr 
{

class Settings;

class EnvDetecter
{
public:
   const char* IS_DETECT_KEY = "env_detected";
public:
   EnvDetecter(Settings& settings);
   void detect();
private:
   bool isNeedDetect() const;
   bool detectGit();
   bool detectGzip();
   bool detectSencha();
   bool detectRpmbuild();
private:
   Settings& m_settings;
   QStringList m_needInstalledTools;
};

}//releasemgr

#endif // RMMGR_UTILS_ENV_DETECTER_H
