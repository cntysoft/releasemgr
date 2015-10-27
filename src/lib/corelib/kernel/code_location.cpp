#include "code_location.h"

#include <QDataStream>
#include <QSharedData>
#include <QString>

namespace releasemgr
{

class CodeLocation::CodeLocationPrivate : public QSharedData
{
public:
   QString filepath;
   int line;
   int column;
};

CodeLocation::CodeLocation(const QString &filepath, int line, int column, bool checkPath)
   :d(new CodeLocationPrivate)
{
   d->filepath = filepath;
   d->line = line;
   d->column = column;
}

}//releasemgr