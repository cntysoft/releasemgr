#ifndef OPTION_POOL
#define OPTION_POOL
#include "global/global.h"

QT_BEGIN_NAMESPACE
class QCommandLineOption;
QT_END_NAMESPACE
namespace releasemgr
{

class OptionPool
{
public:
   OptionPool();
   QCommandLineOption& getFhzcOptions() const;
   QCommandLineOption& getFhShopOptions() const;
   QCommandLineOption& getDeployOptions() const;
   QCommandLineOption& getReleaseMgrOptions() const;
   QCommandLineOption& getConfigOptions() const;
private:
   QCommandLineOption* fhzcOptions;
   QCommandLineOption* fhShopOptions;
   QCommandLineOption* deployOptions;
   QCommandLineOption* releaseMgrOptions;
   QCommandLineOption* configOptions;
};

}

#endif // OPTION_POOL

