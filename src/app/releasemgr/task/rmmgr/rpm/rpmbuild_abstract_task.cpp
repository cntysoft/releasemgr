#include "rpmbuild_abstract_task.h"
#include "task/abstract_taskmgr.h"
#include "const.h"

namespace releasemgr{
namespace task{
namespace rmmgr{
namespace rpmbuild{

RpmBuildAbstractTask::RpmBuildAbstractTask(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs)
   :AbstractTask(taskmgr, invokeArgs)
{
   if(m_invokeArgs.contains(QLatin1String("projectDir"))){
      m_projectDir = m_invokeArgs[QLatin1String("projectDir")].toString();
   }
   if(m_invokeArgs.contains(QLatin1String("buildDir"))){
      m_buildDir = m_invokeArgs[QLatin1String("buildDir")].toString();
   }
   m_rpmBuildDir = m_buildDir+DS+"BUILD";
   m_rpmRpmDir = m_buildDir+DS+"RPMS";
   m_rpmSourceDir = m_buildDir+DS+"SOURCES";
   m_rpmSpecDir = m_buildDir+DS+"SPECS";
   m_rpmSRpmDir = m_buildDir+DS+"SRPMS";
   m_rpmBuildRootDir = m_rpmBuildRootDir+"BUILDROOT";
}

QString RpmBuildAbstractTask::getAssetDir()
{
   return AbstractTask::getAssetDir() + DS+"rmmgr";
}

RpmBuildAbstractTask::~RpmBuildAbstractTask()
{}


}//rpmbuild
}//rmmgr
}//task
}//releasemgr