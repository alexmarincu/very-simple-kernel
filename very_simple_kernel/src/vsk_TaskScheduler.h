/*----------------------------------------------------------------------------*/
#ifndef VSK_TASKSCHEDULER_H
#define VSK_TASKSCHEDULER_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_TaskScheduler vsk_TaskScheduler;
/*----------------------------------------------------------------------------*/
#include "../../c_tool_box/c_tool_box/src/ctb_LinkedList.h"
#include "vsk_Task.h"
/*----------------------------------------------------------------------------*/
typedef void (*vsk_TaskSchedulerOnStart)(void);
typedef void (*vsk_TaskSchedulerOnIdle)(void);
/*----------------------------------------------------------------------------*/
struct vsk_TaskScheduler {
    ctb_LinkedList _tasks;
    vsk_TaskSchedulerOnStart _onStart;
    vsk_TaskSchedulerOnIdle _onIdle;
};
/*----------------------------------------------------------------------------*/
vsk_TaskScheduler * vsk_TaskScheduler_(void);
vsk_TaskScheduler * vsk_TaskScheduler_init(
    vsk_TaskScheduler * const self,
    vsk_TaskSchedulerOnStart const onStart,
    vsk_TaskSchedulerOnIdle const onIdle
);
void vsk_TaskScheduler_start(vsk_TaskScheduler * const self);
void vsk_TaskScheduler_register(
    vsk_TaskScheduler * const self, vsk_Task * const task
);
#endif // VSK_TASKSCHEDULER_H
