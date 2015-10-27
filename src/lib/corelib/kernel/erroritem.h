#ifndef ERRORITEM
#define ERRORITEM

#include "global/global.h"
#include <QExplicitlySharedDataPointer>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

namespace releasemgr 
{

class CodeLocation;

class ErrorItem
{
public:
   ErrorItem();
   ErrorItem(const ErrorItem &rhs);
   ErrorItem& operator=(const ErrorItem &rhs);
   ~ErrorItem() = default;
   
   QString getDescription() const;
   CodeLocation getCodeLocation()const;
   QString toString() const;
   
private:
   ErrorItem(const QString &description, const CodeLocation &codeLocation);
   class ErrorItemPrivate;
   QExplicitlySharedDataPointer<ErrorItemPrivate> d;
};
}

#endif // ERRORITEM

