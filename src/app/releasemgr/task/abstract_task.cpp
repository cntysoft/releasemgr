#include <QStringList>

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

QStringList AbstractTask::getChildKeys(const QString &path)
{
   QString gPath = m_taskmgr.getModuleName();
   if(!path.isEmpty()){
      gPath = gPath + '.' + path;
   }
   return m_settings.getChildKeys(gPath);
}

void AbstractTask::writeLine(const char *msg, TerminalColor color, bool withNewLine)
{
   Terminal::writeText("> ", TerminalColor::Green);
   Terminal::writeText(msg, color);
   if(withNewLine){
      Terminal::writeText("\n");
   }
}

void AbstractTask::writeMsg(const char *msg, TerminalColor color)
{
   Terminal::writeText(msg, color);
}

void AbstractTask::writeBeginMsg(const char *msg)
{
   writeLine(msg, TerminalColor::Default, false);
}

void AbstractTask::writeDoneMsg()
{
   Terminal::writeText("done\n", TerminalColor::Green);
}


AbstractTask::~AbstractTask()
{}

}//releasemgr