#ifndef ASSERT
#define ASSERT

#include "global/global.h"

namespace releasemgr
{
namespace internal
{

RM_EXPORT void write_assert_location(const char *condition, const char *file, int line);
RM_EXPORT Q_NORETURN void throw_assert_location(const char *condition, const char *file, int line);

}//internal
}//releasemgr


#endif // ASSERT