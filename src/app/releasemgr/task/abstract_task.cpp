#include "abstract_task.h"
#include "types.h"
#include "settings.h"

namespace releasemgr 
{

AbstractTask::AbstractTask(AbstractTaskMgr &taskmgr)
   : m_taskmgr(taskmgr), m_settings(taskmgr.getSysSettings())
{
}

QVariant AbstractTask::getSysCfgValue(const QString &key, const QVariant &defaultValue)
{
   return m_settings.getValue(key, m_taskmgr.getModuleName(), defaultValue);
}

AbstractTask::~AbstractTask()
{}

}//releasemgr