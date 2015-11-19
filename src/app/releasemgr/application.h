#ifndef APPLICATION
#define APPLICATION

#include<QCoreApplication>

#include "settings.h"

QT_BEGIN_NAMESPACE
class QObject;
class QEvent;
QT_END_NAMESPACE
namespace releasemgr
{

class Application : public QCoreApplication
{
   Q_OBJECT
public:
   Application(int &argc, char **argv);
   bool notify(QObject * receiver, QEvent * event);
   static Application *instance();
   const Settings& getSettings() const;
private:
   Settings m_settings;
};

}//releasemgr

#endif // APPLICATION

