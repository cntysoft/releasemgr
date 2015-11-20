#ifndef ABSTRACT_TASK_H
#define ABSTRACT_TASK_H

#include "task/abstract_taskmgr.h"

namespace releasemgr 
{

class Settings;

class AbstractTask
{
public:
   AbstractTask(AbstractTaskMgr& taskmgr);
public:
   virtual ~AbstractTask();
   
protected:
   AbstractTaskMgr& m_taskmgr;
   Settings& m_settings;
};

}//relasemgr

#endif // ABSTRACT_TASK_H
