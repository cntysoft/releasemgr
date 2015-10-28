#ifndef CODE_LOCATION
#define CODE_LOCATION

#include "global/global.h"

#include <QExplicitlySharedDataPointer>
#include <QDebug>

QT_BEGIN_NAMESPACE
class QDataStream;
class QString;
QT_END_NAMESPACE

namespace releasemgr
{

class RMGR_EXPORT CodeLocation
{
   friend RMGR_EXPORT bool operator==(const CodeLocation &cl1, const CodeLocation &cl2);
public:
   CodeLocation();
   CodeLocation(const QString &filePath, int line = -1, int column = -1);
   CodeLocation(const CodeLocation &other);
   CodeLocation &operator=(const CodeLocation &other);
   ~CodeLocation();
   
   QString getFilePath() const;
   int getLine() const;
   int getColumn() const;
   
   bool isValid() const;
   QString toString() const;
private:
   class CodeLocationPrivate;
   QExplicitlySharedDataPointer<CodeLocationPrivate> d;
   
};

RMGR_EXPORT bool operator==(const CodeLocation &cl1, const CodeLocation &cl2);
RMGR_EXPORT bool operator!=(const CodeLocation &cl1, const CodeLocation &cl2);

QDebug operator<<(QDebug debug, const CodeLocation &location);

}//releasemgr

#endif // CODE_LOCATION

