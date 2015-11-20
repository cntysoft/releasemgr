#include "abstract_task.h"

namespace releasemgr 
{

AbstractTask::AbstractTask(AbstractTaskMgr &taskmgr)
   : m_taskmgr(taskmgr), m_settings(taskmgr.getSysSettings())
{
}

AbstractTask::~AbstractTask()
{}

}//releasemgr