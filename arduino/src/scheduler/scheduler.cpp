#include "Scheduler.h"

Scheduler::Scheduler(unsigned long basePeriod) : basePeriod(basePeriod) {
    nTasks = 0;
    lastRun = millis();
}

bool Scheduler::addTask(Task* task) {
    if (nTasks < MAX_TASKS - 1) {
        taskList[nTasks] = task;
        nTasks++;
        return true;
    } else {
        return false; 
    }
}

void Scheduler::schedule() {   
    unsigned long now = millis();

    // se non è ancora passato il periodo base, non facciamo nulla
    if (now - lastRun < basePeriod){
        return;
    }

    // aggiorna il riferimento
    lastRun = now;

    for (int i = 0; i < nTasks; i++){
        if ( ! taskList[i]->isActive()) {
            continue; // skip loop
        } 
        
        if (taskList[i]->isPeriodic()) {
            if (taskList[i]->updateAndCheckTime(basePeriod)) {
                taskList[i]->tick();
            }
        } else { // aperiodic
            taskList[i]->tick();
            if (taskList[i]->isCompleted()){
                taskList[i]->setActive(false);
            }
        }
    }
    
}



