#include "Task.h"
#include "user_usart.h"

uint8_t tot = 0; // counter for tasks, tot == 0 for no task
uint8_t CheckStcik = 0; // Check Stick
Task Tasks[max_tasks_num];

Task *TaskAdd(void (*TaskFunction)(void), uint8_t Period){
    Tasks[++tot].TaskFunction = TaskFunction;
    Tasks[tot].Running = false;
    Tasks[tot].Period = (Period < 0) ? 0 : Period; // make sure Period >= 0
    Tasks[tot].Waiting = 0;
    Tasks[tot].IsOn = true; // Defaults to run the task
    Tasks[tot].TimeTick = Tasks[tot].DeltaTime = 0; // Reset TimeTick
    Tasks[tot].PrintDeltaTime = false; // Defaults not to print
    return &Tasks[tot];
}

void TaskCheck(){
    CheckStcik++;
    for(uint8_t i = 1; i <= tot; i++){
        // Only check task that is on and waiting
        if(Tasks[i].IsOn && Tasks[i].Waiting){
            Tasks[i].Waiting--;
        }
    }
}

void TaskRun(){
    for(uint8_t i = 1; i <= tot; i++){
        // Only run task that is on, not running and not waiting
        if(Tasks[i].IsOn && !Tasks[i].Running && !Tasks[i].Waiting){
            Tasks[i].Waiting = Tasks[i].Period; // Reset Waiting Period
            Tasks[i].DeltaTime = CheckStcik - Tasks[i].TimeTick; // Calculate delta time
            if(Tasks[i].PrintDeltaTime) usart_printf("Task No.%d DeltaTime: %d\n", i, Tasks[i].DeltaTime);
            Tasks[i].TimeTick = CheckStcik; // Update TimeTick
            Tasks[i].Running = true;
            Tasks[i].TaskFunction();
            Tasks[i].Running = false;
        }
    }
}

void TaskOn(Task *task){
    task -> IsOn = true;
}

void TaskOff(Task *task){
    task -> IsOn = false;
}

void TaskPrintDeltaTime(Task *task){
    task -> PrintDeltaTime = true;
}