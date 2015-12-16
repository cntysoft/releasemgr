#ifndef RELEASEMGR_TASK_FHSHOP_DIFFBUILD_GENERATE_DIFF_METAINFO_H
#define RELEASEMGR_TASK_FHSHOP_DIFFBUILD_GENERATE_DIFF_METAINFO_H

#include <QMap>

#include "diffbuild_abstract_task.h"

class AbstractTaskMgr;

QT_BEGIN_NAMESPACE
class QString;
class QStringList;
QT_END_NAMESPACE

namespace releasemgr{
namespace task{
namespace fhshop{
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
   void buildAndCopyFiles(const GeneralKeyToListMapType& savedMetaInfo, const QStringList& needRunCmdProjects);
   void saveDiffMetaInfo(GeneralKeyToListMapType& savedMetaInfo, const GeneralKeyToListMapType& modifiedFiles, const QStringList& needRunCmdProjects);
   void getSubmoduleHash(const QString& projectDir, const QString& versionTag, const QStringList& submodules, SubmoduleHashMapType& hashs);
   void getGitDiffFiles(const QString& projectDir, const QString& from, const QString& to, GeneralKeyToListMapType& modifiedFilesMap, const QStringList& paths = QStringList(), const QStringList& skips = QStringList());
   void execSenchaCmd(const QString& projectDir);
private:
   bool m_needRunSenchaCmd = false;
};

}//diffbuild
}//fhshop
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_FHSHOP_DIFFBUILD_GENERATE_DIFF_METAINFO_H
