#include "application.h"
#include "kernel/errorinfo.h"
#include "global/common_funcs.h"
namespace releasemgr 
{

Application::Application(int &argc, char **argv)\
   :QCoreApplication(argc, argv)
{
   setApplicationName(QLatin1String("releasemgr"));
   setOrganizationName(QLatin1String("sheneninfo technology"));
   setOrganizationDomain(QLatin1String("www.fhzc.com"));
}

Application *Application::instance()
{
   return qobject_cast<Application *>(QCoreApplication::instance());
}

bool Application::notify(QObject *receiver, QEvent *event)
{
   try{
      return QCoreApplication::notify(receiver, event);
   }catch(const ErrorInfo& errorInfo){
      qDebug() << errorInfo.toString();
      QCoreApplication* app = get_core_application();
      app->exit(EXIT_FAILURE);
      return false;
   }
}

}//releasemgr