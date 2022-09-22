#include "Scheduler.h"
#include "BlinkTask.h"
#include "ThreeLedsTask.h"

Scheduler sched;

void setup(){
  
  sched.init(50);
  
  Task* t0 = new BlinkTask(10); //indico il pin del led
  t0->init(500); //ogni quanto fare questo task
  sched.addTask(t0);

  Task* t1 = new ThreeLedsTask(7,8,9); //init led
  t1->init(150); //ogni quanto fare questo task
  sched.addTask(t1);  
    
}

void loop(){
  sched.schedule();
}
