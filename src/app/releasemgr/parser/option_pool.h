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
//   QCommandLineOption& getFhzcOption() const;
//   QCommandLineOption& getFhShopOption() const;
//   QCommandLineOption& getDeployOption() const;
//   QCommandLineOption& getReleaseMgrOption() const;
//   QCommandLineOption& getConfigOption() const;
//private:
//   QCommandLineOption *fhzcOption;
//   QCommandLineOption *fhShopOption;
//   QCommandLineOption *deployOption;
//   QCommandLineOption *releaseMgrOption;
//   QCommandLineOption *configOption;
};

}

#endif // OPTION_POOL

