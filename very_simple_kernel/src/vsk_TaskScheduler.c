/*----------------------------------------------------------------------------*/
#include "vsk_TaskScheduler.h"
/*----------------------------------------------------------------------------*/
#include "../../c_tool_box/c_tool_box/src/ctb.h"
#include "vsk_OnStartEvent.h"
/*----------------------------------------------------------------------------*/
vsk_TaskScheduler * vsk_TaskScheduler_(void) {
    static vsk_TaskScheduler self;
    return &self;
}
/*----------------------------------------------------------------------------*/
vsk_TaskScheduler * vsk_TaskScheduler_init(
    vsk_TaskScheduler * const self,
    vsk_TaskSchedulerOnStart const onStart,
    vsk_TaskSchedulerOnIdle const onIdle
) {
    ctb_LinkedList_init(&self->_tasks);
    self->_onStart = onStart;
    self->_onIdle = onIdle;
    return self;
}
/*----------------------------------------------------------------------------*/
static bool vsk_isTaskReady(vsk_Task * const task) {
    return vsk_Task_isReady(task);
}
/*----------------------------------------------------------------------------*/
void vsk_TaskScheduler_start(vsk_TaskScheduler * const self) {
    self->_onStart();
    vsk_Event_raise((vsk_Event *)vsk_OnStartEvent_());
    while (1) {
        vsk_Task * readyTask =
            ctb_containerOf(
                ctb_LinkedList_find(
                    &self->_tasks,
                    (ctb_LinkedListIteratorFindPredicate)vsk_isTaskReady
                ),
                vsk_Task,
                _super.node
            );
        if (readyTask) {
            vsk_Task_run(readyTask);
        } else {
            self->_onIdle();
        }
    }
}
/*----------------------------------------------------------------------------*/
void vsk_TaskScheduler_register(
    vsk_TaskScheduler * const self, vsk_Task * const task
) {
    ctb_LinkedList_addLast(&self->_tasks, vsk_Task_toNode(task));
}
