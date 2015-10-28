#include "erroritem.h"
#include "code_location.h"
#include <QSharedData>

namespace releasemgr 
{
class ErrorItem::ErrorItemPrivate : public QSharedData
{
public:
   QString description;
   CodeLocation codeLocation;
};

ErrorItem::ErrorItem()
   :d(new ErrorItemPrivate)
{
}

ErrorItem::~ErrorItem()
{}

ErrorItem::ErrorItem(const QString &description, const CodeLocation &codeLocation)
   :d(new ErrorItemPrivate)
{
   d->description = description;
   d->codeLocation = codeLocation;
}

ErrorItem::ErrorItem(const ErrorItem &rhs)
   :d(rhs.d)
{
}

ErrorItem& ErrorItem::operator=(const ErrorItem &rhs)
{
   d = rhs.d;
   return *this;
}

QString ErrorItem::getDescription() const
{
   return d->description;
}

CodeLocation ErrorItem::getCodeLocation() const
{
   return d->codeLocation;
}

QString ErrorItem::toString() const
{
   QString str = getCodeLocation().toString();
   if(!str.isEmpty()){
      str += QLatin1Char(' ');
   }
   return str += getDescription();
}

}//relasemgr