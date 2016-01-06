#include <QString>

#include "rpmbuild_abstract_task.h"
#include "task/abstract_taskmgr.h"
#include "const.h"
#include "corelib/kernel/errorinfo.h"
#include "corelib/io/filesystem.h"

namespace releasemgr{
namespace task{
namespace cloudcontroller{
namespace rpmbuild{

using sn::corelib::ErrorInfo;
using sn::corelib::Filesystem;

RpmBuildAbstractTask::RpmBuildAbstractTask(const AbstractTaskMgr& taskmgr, const TaskParamsType& invokeArgs)
   :AbstractTask(taskmgr, invokeArgs)
{
   if(m_invokeArgs.contains("projectDir")){
      m_projectDir = m_invokeArgs["projectDir"];
   }
   if(m_invokeArgs.contains("buildDir")){
      m_buildDir = m_invokeArgs["buildDir"];
   }
   if(!Filesystem::dirExist(m_projectDir)){
      throw ErrorInfo(QString("项目文件夹 %1 不存在").arg(m_projectDir));
   }
   m_rpmBuildDir = m_buildDir+DS+"BUILD";
   m_rpmRpmDir = m_buildDir+DS+"RPMS";
   m_rpmSourceDir = m_buildDir+DS+"SOURCES";
   m_rpmSpecDir = m_buildDir+DS+"SPECS";
   m_rpmSRpmDir = m_buildDir+DS+"SRPMS";
   m_rpmBuildRootDir = m_buildDir+DS+"BUILDROOT";
}

QString RpmBuildAbstractTask::getAssetDir()
{
   return AbstractTask::getAssetDir() + DS+"cloudcontroller";
}

RpmBuildAbstractTask::~RpmBuildAbstractTask()
{}

}//rpmbuild
}//cloudcontroller
}//task
}//releasemgr