#ifndef ABSTRACT_TASK_H
#define ABSTRACT_TASK_H

#include <QVariant>

#include "task/abstract_taskmgr.h"
#include "types.h"
#include "global/global.h"

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
   QVariant getSysCfgValue(const QString& key, const QVariant & defaultValue = QVariant());
public:
   virtual void exec() = 0;
   virtual ~AbstractTask();
protected:
   void runCmd(const QLatin1String& cmd, const TaskParamsType& args, const QString& cwd);
protected:
   const AbstractTaskMgr& m_taskmgr;
   Settings& m_settings;
   const TaskParamsType& m_invokeArgs;
};

}//relasemgr

#endif // ABSTRACT_TASK_H
