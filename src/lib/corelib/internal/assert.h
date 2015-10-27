#ifndef ASSERT
#define ASSERT

#include "global/global.h"

namespace releasemgr
{
namespace internal
{

RMGR_EXPORT void write_assert_location(const char *condition, const char *file, int line);
RMGR_EXPORT Q_NORETURN void throw_assert_location(const char *condition, const char *file, int line);

}//internal
}//releasemgr

#define RMGR_ASSERT(cond, action)\
   if(Q_LIKELY(cond)){} else {\
      ::releasemgr::internal::write_assert_location(#cond, __FILE__, __LINE__);action;\
   } do{}while(0)

// The do{}while (0) is here to enforce the use of a semicolon after RMGR_ASSERT.
// action can also be continue or break. 
#define RMGR_CHECK(cond)\
   do{\
      if(Q_LIKELY(cond)){} else {\
        ::releasemgr::internal::throw_assert_location(#cond, __FILE__, __LINE__);\
      }\
   }while(0)

#endif // ASSERT