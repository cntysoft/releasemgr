#ifndef APPLICATION
#define APPLICATION

#include<QCoreApplication>

namespace releasemgr
{

class Application : public QCoreApplication
{
   Q_OBJECT
public:
   Application(int &argc, char **argv);
   static Application *instance();
};

}//releasemgr

#endif // APPLICATION

