#ifndef RELEASEMGR_UTILS_ENV_DETECTER_H
#define RELEASEMGR_UTILS_ENV_DETECTER_H

#include <QStringList>

#include "kernel/settings.h"

namespace releasemgr 
{

using sn::corelib::Settings;

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

#endif // RELEASEMGR_UTILS_ENV_DETECTER_H
