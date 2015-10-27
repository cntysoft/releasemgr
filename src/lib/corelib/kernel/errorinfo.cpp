#include <QString>
#include <QList>
#include <QSharedData>
#include "errorinfo.h"
#include "erroritem.h"

namespace releasemgr 
{

class ErrorInfo::ErrorInfoPrivate : public QSharedData
{
public:
   ErrorInfoPrivate()
      : internalError(false)
   {}
   QList<ErrorItem> items;
   bool internalError;
};

ErrorInfo::ErrorInfo()
   : d(new ErrorInfoPrivate)
{
   
}

ErrorInfo::ErrorInfo(const ErrorInfo &rhs)
   :d(rhs.d)
{
   
}

ErrorInfo::ErrorInfo(const QString &description, const CodeLocation &codeLocation, bool internalError)
   :d(new ErrorInfoPrivate)
{
   append(description, codeLocation);
   d->internalError = internalError;
}

ErrorInfo& ErrorInfo::operator=(const ErrorInfo &other)
{
   d = other.d;
   return *this;
}

void ErrorInfo::append(const QString &description, const CodeLocation &codeLocation)
{
   d->items.append(ErrorItem(description, codeLocation));
}

void ErrorInfo::prepend(const QString &description, const CodeLocation &codeLocation)
{
   d->items.prepend(description, location);
}

QList<ErrorItem> ErrorInfo::getItems() const
{
   return d->items;
}

void ErrorInfo::clear()
{
   d->items.clear();
}

QString ErrorInfo::toString() const
{
   QStringList lines;
   foreach (const ErrorItem &error, d->items) {
      lines.append(error.toString());
   }
   return lines.join(QLatin1Char('\n'));
}

bool ErrorInfo::isInternalError() const
{
   return d->internalError;
}
}//releasemgr