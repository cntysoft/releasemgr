#ifndef RELEASEMGR_TASK_ZHUCHAO_WEB_DIFF_BUILD_TASKS_H
#define RELEASEMGR_TASK_ZHUCHAO_WEB_DIFF_BUILD_TASKS_H

#include <QMap>
#include <QMap>
#include <QSqlDatabase>

#include "task/abstract_task.h"

QT_BEGIN_NAMESPACE
class QStringList;
class QVariant;
QT_END_NAMESPACE

class AbstractTaskMgr;

QT_BEGIN_NAMESPACE
class QString;
class QStringList;
QT_END_NAMESPACE

namespace releasemgr{
namespace task{
namespace zhuchaoweb{
namespace diffbuild{

class DiffBuildAbstractTask : public AbstractTask
{
public:
   DiffBuildAbstractTask(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
protected:
   QString m_from;
   QString m_to;
public:
   virtual ~DiffBuildAbstractTask();
};

class Clear : public DiffBuildAbstractTask
{
public:
   Clear(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~Clear();
};

class GenerateDiffMetaInfo : public DiffBuildAbstractTask
{
public:
   using SubmoduleHashMapType = QMap<QString, QString>;
   using GeneralKeyToListMapType = QMap<QString, QStringList>;
public:
   GenerateDiffMetaInfo(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~GenerateDiffMetaInfo();
private:
   void collectModifiedSubmodules(QStringList& modifiedSubmodules, SubmoduleHashMapType& fromHashs, SubmoduleHashMapType& toHashs);
   void collectModifiedFiles(GeneralKeyToListMapType& modifiedFiles, const QStringList& modifiedSubmodules, const SubmoduleHashMapType& fromHashs, const SubmoduleHashMapType& toHashs);
   void collectNeedRunCmdProjects(QStringList& projects, const GeneralKeyToListMapType& modifiedFilenames);
   void buildAndCopyFiles(const GeneralKeyToListMapType& savedMetaInfo, const QStringList& needRunCmdProjects);
   void saveDiffMetaInfo(GeneralKeyToListMapType& savedMetaInfo, const GeneralKeyToListMapType& modifiedFiles, const QStringList& needRunCmdProjects);
   void getSubmoduleHash(const QString& projectDir, const QString& versionTag, const QStringList& submodules, SubmoduleHashMapType& hashs);
   void getGitDiffFiles(const QString& projectDir, const QString& from, const QString& to, GeneralKeyToListMapType& modifiedFilesMap, const QStringList& paths = QStringList(), const QStringList& skips = QStringList());
   void execSenchaCmd(const QString& projectDir);
private:
   bool m_needRunSenchaCmd = false;
};

class GenerateVersionInfo : public DiffBuildAbstractTask
{
public:
   GenerateVersionInfo(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~GenerateVersionInfo();
};

class SetupDistConst : public DiffBuildAbstractTask
{
public:
   SetupDistConst(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~SetupDistConst();
};

class AnalysisDatabase : public DiffBuildAbstractTask
{
public:
   using ColMetaType = QMap<QString, QVariant>;
   using ColItemsType = QMap<QString, ColMetaType>;
public:
   AnalysisDatabase(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~AnalysisDatabase();
private:
   void changeDatabases(const QString dbnamePrefix);
   void doAnalisys(const QString dbnamePrefix, QByteArray &metaJsonData);
   ColItemsType getTableColumns(const QString& schema, const QString& tableName);
private:
   QSqlDatabase m_fromDb;
   QSqlDatabase m_toDb;
};

class CopyUpgradeScript : public DiffBuildAbstractTask
{
public:
   CopyUpgradeScript(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~CopyUpgradeScript();
private:
   void doCopyScript(const QString filenamePrefix);
};

class Compress : public DiffBuildAbstractTask
{
public:
   Compress(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs);
public:
   virtual void exec();
   virtual ~Compress();
private:
   void execGzipCmd(const QString& savedFilename, const QString& sourceDir);
};

}//diffbuild
}//zhuchaoweb
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_ZHUCHAO_WEB_DIFF_BUILD_TASKS_H
