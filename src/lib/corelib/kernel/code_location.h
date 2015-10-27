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

class RM_EXPORT CodeLocation
{
   friend RM_EXPORT bool operator==(const CodeLocation &cl1, const CodeLocation &cl2);
public:
   CodeLocation() = default;
   CodeLocation(const QString &filePath, int line = -1, int column = -1, bool checkPath = true);
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

RM_EXPORT bool operator==(const CodeLocation &cl1, const CodeLocation &cl2);
RM_EXPORT bool operator!=(const CodeLocation &cl1, const CodeLocation &cl2);

QDebug operator<<(QDebug debug, const CodeLocation &location);

}//releasemgr

#endif // CODE_LOCATION

