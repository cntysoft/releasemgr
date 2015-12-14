#ifndef RELEASEMGR_TASK_ABSTRACT_TASK_H
#define RELEASEMGR_TASK_ABSTRACT_TASK_H

#include <QVariant>

#include "task/abstract_taskmgr.h"
#include "types.h"
#include "global/global.h"
#include "io/terminal.h"

QT_BEGIN_NAMESPACE
class QString;
class QLatin1String;
class QStringList;
QT_END_NAMESPACE

namespace releasemgr 
{

class Settings;

class AbstractTask
{
   Q_DISABLE_COPY(AbstractTask)
public:
   AbstractTask(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec() = 0;
   virtual ~AbstractTask();
protected:
   void runCmd(const QLatin1String& cmd, const TaskParamsType& args, const QString& cwd);
   void writeLine(const char* msg, TerminalColor color = TerminalColor::Default, bool withNewLine = true);
   void writeMsg(const char* msg, TerminalColor color = TerminalColor::Default);
   void writeBeginMsg(const char* msg);
   void writeDoneMsg();
   QVariant getSysCfgValue(const QString& key, const QVariant & defaultValue = QVariant());
   QStringList getChildKeys(const QString& path = QString());
protected:
   virtual QString getAssetDir();
protected:
   const AbstractTaskMgr& m_taskmgr;
   Settings& m_settings;
   const TaskParamsType& m_invokeArgs;
   QString m_projectDir;
   QString m_buildDir;
};

}//relasemgr

#endif // RELEASEMGR_TASK_ABSTRACT_TASK_H
