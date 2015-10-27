#include "assert.h"

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
   
}

}//internal
}//releasemgr