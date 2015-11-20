#include "application.h"
#include "kernel/errorinfo.h"
#include "utils/funcs.h"
#include "io/terminal.h"

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
         str += '\n';
         Terminal::writeText(str.toLatin1(), TerminalColor::Red);
      }
      const Application& app = get_app_ref();
      app.exit(EXIT_FAILURE);
      return false;
   }
}

Settings& Application::getSettings()
{
   return m_settings;
}

}//releasemgr