#ifndef TASK_FHZC_FULLBUILD_DUMP_MYSQL_H
#define TASK_FHZC_FULLBUILD_DUMP_MYSQL_H

#include "fullbuild_abstract_task.h"

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

namespace releasemgr{
namespace task{
namespace fhzc{
namespace fullbuild{

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

}//fullbuild
}//fhzc
}//task
}//releasemgr

#endif // TASK_FHZC_FULLBUILD_DUMP_MYSQL_H
