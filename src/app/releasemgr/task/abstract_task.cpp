#include "abstract_task.h"
#include "types.h"
#include "settings.h"

namespace releasemgr 
{

AbstractTask::AbstractTask(const AbstractTaskMgr &taskmgr, const TaskParamsType& invokeArgs)
   : m_taskmgr(taskmgr), m_settings(taskmgr.getSysSettings()), m_invokeArgs(invokeArgs)
{
   m_projectDir = getSysCfgValue("projectDir").toString();
   m_buildDir = getSysCfgValue("buildDir").toString();
}

QVariant AbstractTask::getSysCfgValue(const QString &key, const QVariant &defaultValue)
{
   return m_settings.getValue(key, m_taskmgr.getModuleName(), defaultValue);
}

void AbstractTask::writeLine(const char *msg, TerminalColor color)
{
   Terminal::writeText("> ", TerminalColor::Green);
   Terminal::writeText(msg, color);
   Terminal::writeText("\n");
}

AbstractTask::~AbstractTask()
{}

}//releasemgr