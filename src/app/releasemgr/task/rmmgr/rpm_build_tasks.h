#ifndef RELEASEMGR_TASK_RMMGR_RPM_BUILD_TASKS_H
#define RELEASEMGR_TASK_RMMGR_RPM_BUILD_TASKS_H

#include "task/abstract_task.h"

QT_BEGIN_NAMESPACE
class QLatin1String;
QT_END_NAMESPACE

class Settings;

namespace releasemgr{
namespace task{
namespace rmmgr{
namespace rpmbuild{

class RpmBuildAbstractTask : public releasemgr::AbstractTask
{
public:
   RpmBuildAbstractTask(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual ~RpmBuildAbstractTask();
protected:
   virtual QString getAssetDir();
protected:
   QString m_rpmSourceDir;
   QString m_rpmBuildDir;
   QString m_rpmSpecDir;
   QString m_rpmRpmDir;
   QString m_rpmSRpmDir;
   QString m_rpmBuildRootDir;
};

class Clear : public RpmBuildAbstractTask 
{
public:
   Clear(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~Clear();
};

class MakeProjectStructure : public RpmBuildAbstractTask 
{
public:
   MakeProjectStructure(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~MakeProjectStructure();
};

class CopySourceFiles : public RpmBuildAbstractTask 
{
public:
   CopySourceFiles(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~CopySourceFiles();
private:
   void processSpecFile();
};

class BuildRpm : public RpmBuildAbstractTask 
{
public:
   BuildRpm(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~BuildRpm();
};

}//rpmbuild
}//rmmgr
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_RMMGR_RPM_BUILD_TASKS_H
