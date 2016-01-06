#include <QString>

#include "rpmbuild_abstract_task.h"
#include "task/abstract_taskmgr.h"
#include "const.h"

namespace releasemgr{
namespace task{
namespace upgrademgrmaster{
namespace rpmbuild{

RpmBuildAbstractTask::RpmBuildAbstractTask(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs)
   :AbstractTask(taskmgr, invokeArgs)
{
   if(m_invokeArgs.contains("projectDir")){
      m_projectDir = m_invokeArgs["projectDir"];
   }
   if(m_invokeArgs.contains("buildDir")){
      m_buildDir = m_invokeArgs["buildDir"];
   }
   m_rpmBuildDir = m_buildDir+DS+"BUILD";
   m_rpmRpmDir = m_buildDir+DS+"RPMS";
   m_rpmSourceDir = m_buildDir+DS+"SOURCES";
   m_rpmSpecDir = m_buildDir+DS+"SPECS";
   m_rpmSRpmDir = m_buildDir+DS+"SRPMS";
   m_rpmBuildRootDir = m_buildDir+"BUILDROOT";
}

QString RpmBuildAbstractTask::getAssetDir()
{
   return AbstractTask::getAssetDir() + DS+"upgrademgr_master";
}

RpmBuildAbstractTask::~RpmBuildAbstractTask()
{}

}//rpmbuild
}//upgrademgrmaster
}//task
}//releasemgr