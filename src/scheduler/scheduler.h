#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"
#include <TimerOne.h>

#define MAX_TASKS 50

class Scheduler {
    unsigned long basePeriod;
    int nTasks;
    Task* taskList[MAX_TASKS];
    unsigned long lastRun;

public:
    Scheduler(int basePeriod);  
    virtual bool addTask(Task* task);  
    virtual void schedule();
};

#endif