#ifndef APPLICATION
#define APPLICATION

#include<QCoreApplication>
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
   static Application *instance();
   bool notify(QObject * receiver, QEvent * event);
};

}//releasemgr

#endif // APPLICATION

