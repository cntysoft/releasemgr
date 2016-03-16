#ifndef RELEASEMGR_TASK_ZHUCHAO_WEB_FULL_BUILD_TASKS_H
#define RELEASEMGR_TASK_ZHUCHAO_WEB_FULL_BUILD_TASKS_H

#include "task/abstract_task.h"

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace zhuchaoweb{
namespace fullbuild{

class FullBuildAbstractTask : public releasemgr::AbstractTask
{
public:
   FullBuildAbstractTask(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual ~FullBuildAbstractTask();
};

class Clear : public FullBuildAbstractTask
{
public:
   Clear(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~Clear();
};

class CopyProjectFiles : public FullBuildAbstractTask
{
public:
   CopyProjectFiles(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~CopyProjectFiles();
private:
   QStringList collectProjectFilenames();
   void collectSpecialFilenames(QStringList& filenames);
};

class GenerateVersionInfo : public FullBuildAbstractTask
{
public:
   GenerateVersionInfo(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~GenerateVersionInfo();
};

class SetupDistConst : public FullBuildAbstractTask
{
public:
   SetupDistConst(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~SetupDistConst();
};

class BuildJsProjects : public FullBuildAbstractTask
{
public:
   BuildJsProjects(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~BuildJsProjects();
private:
   void execSenchaCmd(const QString& projectDir);
};

class DumpMysql : public FullBuildAbstractTask
{
public:
   DumpMysql(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~DumpMysql();
private:
   void execMysqlDumpCmd(const QString& username, const QString& password, const QString& dbname, QString& sql, bool withData = false);
};


class SetupConfig : public FullBuildAbstractTask
{
public:
   SetupConfig(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~SetupConfig();
};

class Compress : public FullBuildAbstractTask
{
public:
   Compress(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~Compress();
private:
   void execGzipCmd(const QString& savedFilename, const QString& sourceDir);
};

}//fullbuild
}//zhuchaoweb
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_ZHUCHAO_WEB_FULL_BUILD_TASKS_H
