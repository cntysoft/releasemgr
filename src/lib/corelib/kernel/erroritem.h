#ifndef RMGR_CORE_KERNEL_CODE_ERRORITEM_H
#define RMGR_CORE_KERNEL_CODE_ERRORITEM_H

#include "global/global.h"
#include <QExplicitlySharedDataPointer>
//#include "code_location.h"
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
   ErrorItem(const QString &description, const CodeLocation &codeLocation);
   ErrorItem(const ErrorItem &rhs);
   ErrorItem& operator=(const ErrorItem &rhs);
   ~ErrorItem();
   
   QString getDescription() const;
   CodeLocation getCodeLocation()const;
   QString toString() const;
   
private:
   class ErrorItemPrivate;
   QExplicitlySharedDataPointer<ErrorItemPrivate> d;
};
}

#endif // RMGR_CORE_KERNEL_CODE_ERRORITEM_H

