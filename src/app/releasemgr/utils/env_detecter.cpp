#include <QVariant>
#include <QDebug>
#include <QFile>

#include "const.h"
#include "utils/env_detecter.h"
#include "settings.h"
#include "io/terminal.h"
#include "utils/funcs.h"
#include "application.h"
#include "kernel/errorinfo.h"

namespace releasemgr 
{

const EnvDetecter::EnvProgramType EnvDetecter::envDetectRepo{
   {QLatin1String("git"), QLatin1String("/usr/bin/gitq")},
   {QLatin1String("gzip"), QLatin1String("/usr/bin/gziqp")},
   {QLatin1String("mysqldump"), QLatin1String("/usr/bin/mysqlqdump")},
   {QLatin1String("sencha"), QLatin1String("/usr/bin/sencha")}
};

EnvDetecter::EnvDetecter(const Settings& settings)
   : m_settings(settings)
{
}

void EnvDetecter::detect() const
{
   if(!isNeedDetect()){
      return;
   }
   //开始探测环境
   QStringList notExistTools;
   EnvProgramType::const_iterator it = envDetectRepo.cbegin();
   while(it != envDetectRepo.cend()){
      QFile binFile(it.value());
      if(!binFile.exists()){
         notExistTools << it.key();
      }
      it++;
   }
   if(!notExistTools.empty()){
      Terminal::writeText("some build tool not install\n", TerminalColor::Red);
      QStringList::const_iterator strIterator = notExistTools.cbegin();
      while(strIterator != notExistTools.cend()){
         QString bin(*strIterator);
         bin += " not found";
         Terminal::writeText(bin.toLocal8Bit(), TerminalColor::Cyan);
         Terminal::writeText("\n", TerminalColor::Cyan);
         strIterator++;
      }
      throw ErrorInfo();
   }
   //将探测结果写入配置文件
   
}

bool EnvDetecter::isNeedDetect()const
{
   return !m_settings.getValue(IS_DETECT_KEY, CFG_GROUP_GLOABL, false).toBool();
}

}//releasemgr