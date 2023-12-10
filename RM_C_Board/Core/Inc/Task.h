# pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct{
    bool IsOn; // Only Run the task when IsOn == True
    bool Running; // True for running
    bool PrintDeltaTime; // True for printing delta time
    uint8_t Period; // Period == 0 means no period running
    uint8_t Waiting; // Waiting == 0 means the task is ready to run
    uint8_t TimeTick; // Start Time Tick
    uint8_t DeltaTime; // DeltaTime between Task running
    void (*TaskFunction)(void); // Task function
}Task;

#define max_tasks_num 10 // Maximum number of tasks, which can be modified for more tasks

Task *TaskAdd(void (*TaskFunction)(void), uint8_t Period); // Add a task and return the task
void TaskCheck(); // Check Task status and update Task status
void TaskRun(); // Run Task
void TaskOn(Task *task); // Make the task On
void TaskOff(Task *task); // Make the task Off
void TaskPrintDeltaTime(Task *task); // Set PrintDeltaTime to On