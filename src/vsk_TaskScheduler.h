/*----------------------------------------------------------------------------*/
#ifndef VSK_TASKSCHEDULER_H
#define VSK_TASKSCHEDULER_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_TaskScheduler vsk_TaskScheduler;
/*----------------------------------------------------------------------------*/
#include "ctb_DList.h"
#include "vsk_Task.h"
/*----------------------------------------------------------------------------*/
typedef void (*vsk_TaskSchedulerOnStart)(void);
typedef void (*vsk_TaskSchedulerOnIdle)(void);
/*----------------------------------------------------------------------------*/
struct vsk_TaskScheduler {
    ctb_DList_t              tasks;
    vsk_TaskSchedulerOnStart onStart;
    vsk_TaskSchedulerOnIdle  onIdle;
};
/*----------------------------------------------------------------------------*/
vsk_TaskScheduler * vsk_TaskScheduler_(void);
vsk_TaskScheduler * vsk_TaskScheduler_init(
    vsk_TaskScheduler * const      self,
    vsk_TaskSchedulerOnStart const onStart,
    vsk_TaskSchedulerOnIdle const  onIdle
);
void vsk_TaskScheduler_start(vsk_TaskScheduler * const self);
void vsk_TaskScheduler_register(
    vsk_TaskScheduler * const self, vsk_Task * const task
);
#endif // VSK_TASKSCHEDULER_H
