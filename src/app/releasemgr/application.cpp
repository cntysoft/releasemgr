#include "application.h"
#include "kernel/errorinfo.h"
#include "global/common_funcs.h"
namespace releasemgr 
{

Application::Application(int &argc, char **argv)
   :QCoreApplication(argc, argv)
{
   setApplicationName(QLatin1String("releasemgr"));
   setOrganizationName(QLatin1String("sheneninfo technology"));
   setOrganizationDomain(QLatin1String("www.sheneninfo.com"));
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
      QString str(errorInfo.toString());
      if(str.size() > 0){
         qDebug() << str;
      }
      QCoreApplication* app = get_core_application();
      app->exit(EXIT_FAILURE);
      return false;
   }
}

}//releasemgr