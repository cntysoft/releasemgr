#ifndef OPTION_POOL
#define OPTION_POOL
#include "global/global.h"
#include <QMap>
#include <QCommandLineOption>

QT_BEGIN_NAMESPACE
class QCommandLineParser;
class QString;
QT_END_NAMESPACE

namespace releasemgr
{

class OptionPool
{
public:
   using OptionMapType = QMap<QString, QCommandLineOption*>;
   OptionPool();
   ~OptionPool();
   OptionMapType& getFhzcOptions();
   OptionMapType& getEntryOptions();
//   OptionMapType& getFhShopOptions() const;
//   OptionMapType& getDeployOptions() const;
//   OptionMapType& getReleaseMgrOptions() const;
//   OptionMapType& getConfigOptions() const;
   
   QCommandLineParser* getFhzcCmdParser();
   QCommandLineParser* getEntryCmdParser();
//   QCommandLineParser* getFhShopCmdParser() const;
//   QCommandLineParser* getDeployCmdParser() const;
//   QCommandLineParser* getReleaseCmdParser() const;
//   QCommandLineParser* getConfigCmdParser() const;
private:
   //   void initFhzcOptions() const;
   //   void initFhShopOptions() const;
   //   void initDeployOptions() const;
   //   void initReleaseMgrOptions() const;
   //   void initConfigOptions() const;
   OptionMapType* m_fhzcOptions = nullptr;
   OptionMapType* m_entryOptions = nullptr;
   
   QCommandLineParser* m_fhzcCmdParser = nullptr;
   QCommandLineParser* m_entryCmdParser = nullptr;
//   OptionMapType* fhShopOptions = nullptr;
//   OptionMapType* deployOptions = nullptr;
//   OptionMapType* releaseMgrOptions = nullptr;
//   OptionMapType* configOptions = nullptr;
   
   
};

}

#endif // OPTION_POOL

