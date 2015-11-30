#ifndef TASK_FHZC_DIFFBUILD_GENERATE_DIFF_METAINFO_H
#define TASK_FHZC_DIFFBUILD_GENERATE_DIFF_METAINFO_H

#include <QMap>

#include "diffbuild_abstract_task.h"

class AbstractTaskMgr;

QT_BEGIN_NAMESPACE
class QString;
class QStringList;
QT_END_NAMESPACE

namespace releasemgr{
namespace task{
namespace fhzc{
namespace diffbuild{

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
   void buildAndCopyFiles();
   void saveDiffMetaInfo(const GeneralKeyToListMapType& modifiedFiles, const QStringList& needRunCmdProjects);
   void getSubmoduleHash(const QString& projectDir, const QString& versionTag, const QStringList& submodules, SubmoduleHashMapType& hashs);
   void getGitDiffFiles(const QString& projectDir, const QString& from, const QString& to, GeneralKeyToListMapType& modifiedFilesMap, const QStringList& paths = QStringList(), const QStringList& skips = QStringList());
private:
   bool m_needRunSenchaCmd = false;
};

}//diffbuild
}//fhzc
}//task
}//releasemgr

#endif // TASK_FHZC_DIFFBUILD_GENERATE_DIFF_METAINFO_H
