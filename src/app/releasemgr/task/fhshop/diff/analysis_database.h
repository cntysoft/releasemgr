#ifndef RELEASEMGR_TASK_FHSHOP_DIFFBUILD_ANALYSIS_DATABASE_H
#define RELEASEMGR_TASK_FHSHOP_DIFFBUILD_ANALYSIS_DATABASE_H

#include <QMap>
#include <QSqlDatabase>

#include "diffbuild_abstract_task.h"

QT_BEGIN_NAMESPACE
class QStringList;

class QVariant;
QT_END_NAMESPACE

class AbstractTaskMgr;

namespace releasemgr{
namespace task{
namespace fhshop{
namespace diffbuild{

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
   void openDatabases();
   ColItemsType getTableColumns(const QString& schema, const QString& tableName);
private:
   QSqlDatabase m_fromDb;
   QSqlDatabase m_toDb;
};

}//diffbuild
}//fhshop
}//task
}//releasemgr

#endif // RELEASEMGR_TASK_FHSHOP_DIFFBUILD_ANALYSIS_DATABASE_H
