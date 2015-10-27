#include "assert.h"
#include "kernel/code_location.h"
#include "kernel/errorinfo.h"
#include <QString>

namespace releasemgr 
{
namespace internal 
{

void write_assert_location(const char *condition, const char *file, int line)
{
   qDebug("SOFT ASSERT: %s in %s:%d", condition, file, line);
}

void throw_assert_location(const char *condition, const char *file, int line)
{
   throw ErrorInfo(QString::fromLatin1("ASSERT: %1").arg(QLatin1String(condition)),
                   CodeLocation(QString::fromLocal8Bit(file), line, -1, false), true);
}

}//internal
}//releasemgr