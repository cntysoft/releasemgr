#include "application.h"

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

}//releasemgr