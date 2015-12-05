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
   OptionMapType& getFhshopOptions();
   //   OptionMapType& getDeployOptions() const;
   //   OptionMapType& getReleaseMgrOptions() const;
   //   OptionMapType& getConfigOptions() const;
   
   QCommandLineParser* getFhzcCmdParser();
   QCommandLineParser* getEntryCmdParser();
   QCommandLineParser* getFhshopCmdParser();
   //   QCommandLineParser* getDeployCmdParser() const;
   //   QCommandLineParser* getReleaseCmdParser() const;
   //   QCommandLineParser* getConfigCmdParser() const;
private:
   OptionMapType* m_entryOptions = nullptr;
   OptionMapType* m_fhzcOptions = nullptr;
   OptionMapType* m_fhshopOptions = nullptr;
   
   QCommandLineParser* m_entryCmdParser = nullptr;
   QCommandLineParser* m_fhzcCmdParser = nullptr;
   QCommandLineParser* m_fhshopCmdParser = nullptr;
   
   //   OptionMapType* deployOptions = nullptr;
   //   OptionMapType* releaseMgrOptions = nullptr;
   //   OptionMapType* configOptions = nullptr;
   
   
};

}

#endif // OPTION_POOL

