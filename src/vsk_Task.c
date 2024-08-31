/*----------------------------------------------------------------------------*/
#include "vsk_Task.h"
/*----------------------------------------------------------------------------*/
#include "vsk_TaskScheduler.h"
#include "vsk_Time.h"
/*----------------------------------------------------------------------------*/
vsk_Task * vsk_Task_init(
    vsk_Task * const self, vsk_TaskOperation const operation, void * const obj
) {
    self->operation           = operation;
    self->obj                 = obj;
    self->state               = vsk_TaskState_suspended;
    self->lastStartTimeMillis = 0;
    self->maxRunTimeMillis    = 0;
    self->minPeriodMillis     = UINT32_MAX;
    self->cpuLoad             = 0;
    vsk_TaskScheduler_register(vsk_TaskScheduler_(), self);
    return self;
}
/*----------------------------------------------------------------------------*/
bool vsk_Task_isReady(vsk_Task * const self) {
    (void)self;
    return self->state == vsk_TaskState_ready;
}
/*----------------------------------------------------------------------------*/
static void vsk_Task_profilingBefore(vsk_Task * const self) {
    uint32_t const startTimeMillis = vsk_Time_getMillisCount(vsk_Time_());
    uint32_t const periodMillis    = startTimeMillis - self->lastStartTimeMillis;
    if (periodMillis < self->minPeriodMillis) {
        self->minPeriodMillis = periodMillis;
    }
    self->cpuLoad             = (self->maxRunTimeMillis * 100) / self->minPeriodMillis;
    self->lastStartTimeMillis = startTimeMillis;
}
/*----------------------------------------------------------------------------*/
static void vsk_Task_profilingAfter(vsk_Task * const self) {
    uint32_t const runTimeMillis =
        vsk_Time_getMillisCount(vsk_Time_()) - self->lastStartTimeMillis;
    if (runTimeMillis > self->maxRunTimeMillis) {
        self->maxRunTimeMillis = runTimeMillis;
    }
}
/*----------------------------------------------------------------------------*/
void vsk_Task_run(vsk_Task * const self) {
    switch (self->state) {
        case vsk_TaskState_ready: {
            self->state = vsk_TaskState_running;
            vsk_Task_profilingBefore(self);
            self->operation(self->obj);
            vsk_Task_profilingAfter(self);
            self->state = vsk_TaskState_suspended;
        } break;
        case vsk_TaskState_suspended:
        case vsk_TaskState_running:
        default: {
            // ignore
        } break;
    }
}
/*----------------------------------------------------------------------------*/
void vsk_Task_activate(vsk_Task * const self) {
    switch (self->state) {
        case vsk_TaskState_suspended: {
            self->state = vsk_TaskState_ready;
        } break;
        case vsk_TaskState_ready:
        case vsk_TaskState_running:
        default: {
            // ignore
        } break;
    }
}
/*----------------------------------------------------------------------------*/
// cppcheck-suppress unusedFunction // API function
void vsk_Task_suspend(vsk_Task * const self) {
    switch (self->state) {
        case vsk_TaskState_running: {
            self->state = vsk_TaskState_suspended;
        } break;
        case vsk_TaskState_suspended:
        case vsk_TaskState_ready:
        default: {
            // ignore
        } break;
    }
}
/*----------------------------------------------------------------------------*/
ctb_DNode_t * vsk_Task_toNode(vsk_Task * const self) {
    return &self->node;
}
