/*----------------------------------------------------------------------------*/
#include "vsk_TaskScheduler.h"
/*----------------------------------------------------------------------------*/
#include "ctb.h"
#include "vsk_OnStartEvent.h"
/*----------------------------------------------------------------------------*/
vsk_TaskScheduler * vsk_TaskScheduler_(void) {
    static vsk_TaskScheduler self;
    return &self;
}
/*----------------------------------------------------------------------------*/
vsk_TaskScheduler * vsk_TaskScheduler_init(
    vsk_TaskScheduler * const      self,
    vsk_TaskSchedulerOnStart const onStart,
    vsk_TaskSchedulerOnIdle const  onIdle
) {
    ctb_DList_init(&self->tasks);
    self->onStart = onStart;
    self->onIdle  = onIdle;
    return self;
}
/*----------------------------------------------------------------------------*/
static bool vsk_isTaskReady(vsk_Task * const task) {
    return vsk_Task_isReady(task);
}
/*----------------------------------------------------------------------------*/
void vsk_TaskScheduler_start(vsk_TaskScheduler * const self) {
    self->onStart();
    vsk_Event_raise((vsk_Event *)vsk_OnStartEvent_());
    while (1) {
        vsk_Task * readyTask =
            ctb_containerOf(
                ctb_DList_find(
                    &self->tasks,
                    (ctb_DListIterator_FindPredicate_t)vsk_isTaskReady
                ),
                vsk_Task,
                node
            );
        if (readyTask) {
            vsk_Task_run(readyTask);
        } else {
            self->onIdle();
        }
    }
}
/*----------------------------------------------------------------------------*/
void vsk_TaskScheduler_register(
    vsk_TaskScheduler * const self, vsk_Task * const task
) {
    ctb_DList_addLast(&self->tasks, vsk_Task_toNode(task));
}
