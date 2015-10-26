#ifndef ERRORITEM
#define ERRORITEM
#include "global/global.h"

QT_BEGIN_NAMESPACE
#include <QString>
QT_END_NAMESPACE

namespace releasemgr 
{
class ErrorItem
{
public:
   ErrorItem();
   ErrorItem(const ErrorItem &rhs);
   ErrorItem &operator=(const ErrorItem &rhs);
   ~ErrorItem();
   
   QString description() const;
   QString toString() const;
   
private:
//   ErrorItem(const QString &description, const )
};
}

#endif // ERRORITEM

