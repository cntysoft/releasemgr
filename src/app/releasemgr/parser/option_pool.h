#ifndef OPTION_POOL
#define OPTION_POOL
#include "global/global.h"
#include <QMap>
QT_BEGIN_NAMESPACE
class QCommandLineOption;
class QCommandLineParser;
class QLatin1String;
QT_END_NAMESPACE

namespace releasemgr
{

class OptionPool
{
//   using OptionMapType = QMap<QLatin1String, QCommandLineOption*>;
public:
   OptionPool();
   int& getFhzcOptions() const;
//   OptionMapType& getFhShopOptions() const;
//   OptionMapType& getDeployOptions() const;
//   OptionMapType& getReleaseMgrOptions() const;
//   OptionMapType& getConfigOptions() const;
   
   QCommandLineParser& getFhzcCmdParser() const;
//   QCommandLineParser& getFhShopCmdParser() const;
//   QCommandLineParser& getDeployCmdParser() const;
//   QCommandLineParser& getReleaseCmdParser() const;
//   QCommandLineParser& getConfigCmdParser() const;
private:
   //   void initFhzcOptions() const;
   //   void initFhShopOptions() const;
   //   void initDeployOptions() const;
   //   void initReleaseMgrOptions() const;
   //   void initConfigOptions() const;
   void* fhzcOptions;
//   OptionMapType* fhShopOptions = nullptr;
//   OptionMapType* deployOptions = nullptr;
//   OptionMapType* releaseMgrOptions = nullptr;
//   OptionMapType* configOptions = nullptr;
   
   
};

}

#endif // OPTION_POOL

