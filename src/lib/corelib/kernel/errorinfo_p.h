#ifndef ERRORINFO_P_H
#define ERRORINFO_P_H
#include <QSharedData>
namespace releasemgr
{
class ErrorInfoPrivate : public QSharedData
{
public:
   ErrorInfoPrivate()
      : internalError(false)
   {}
   QList<ErrorItem> items;
   bool internalError;
};
}//releasemgr


#endif // ERRORINFO_P_H

