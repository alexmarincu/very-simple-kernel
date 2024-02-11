/*----------------------------------------------------------------------------*/
#include "vsk_Task.h"
/*----------------------------------------------------------------------------*/
#include "vsk_TaskScheduler.h"
#include "vsk_Time.h"
/*----------------------------------------------------------------------------*/
vsk_Task * vsk_Task_init(
    vsk_Task * const self, vsk_TaskOperation const operation, void * const obj
) {
    self->_operation = operation;
    self->_obj = obj;
    self->_state = vsk_TaskState_suspended;
    self->_lastStartTimeMillis = 0;
    self->_maxRunTimeMillis = 0;
    self->_minPeriodMillis = -1;
    self->_cpuLoad = 0;
    vsk_TaskScheduler_register(vsk_TaskScheduler_(), self);
    return self;
}
/*----------------------------------------------------------------------------*/
bool vsk_Task_isReady(vsk_Task * const self) {
    return self->_state == vsk_TaskState_ready;
}
/*----------------------------------------------------------------------------*/
static void vsk_Task_profilingBefore(vsk_Task * const self) {
    uint32_t const startTimeMillis = vsk_Time_getMillisCount(vsk_Time_());
    uint32_t const periodMillis = startTimeMillis - self->_lastStartTimeMillis;
    if (periodMillis < self->_minPeriodMillis) {
        self->_minPeriodMillis = periodMillis;
    }
    self->_cpuLoad = (self->_maxRunTimeMillis * 100) / self->_minPeriodMillis;
    self->_lastStartTimeMillis = startTimeMillis;
}
/*----------------------------------------------------------------------------*/
static void vsk_Task_profilingAfter(vsk_Task * const self) {
    uint32_t const runTimeMillis =
        vsk_Time_getMillisCount(vsk_Time_()) - self->_lastStartTimeMillis;
    if (runTimeMillis > self->_maxRunTimeMillis) {
        self->_maxRunTimeMillis = runTimeMillis;
    }
}
/*----------------------------------------------------------------------------*/
void vsk_Task_run(vsk_Task * const self) {
    switch (self->_state) {
        case vsk_TaskState_ready: {
            self->_state = vsk_TaskState_running;
            vsk_Task_profilingBefore(self);
            self->_operation(self->_obj);
            vsk_Task_profilingAfter(self);
            self->_state = vsk_TaskState_suspended;
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
    switch (self->_state) {
        case vsk_TaskState_suspended: {
            self->_state = vsk_TaskState_ready;
        } break;
        case vsk_TaskState_ready:
        case vsk_TaskState_running:
        default: {
            // ignore
        } break;
    }
}
/*----------------------------------------------------------------------------*/
void vsk_Task_suspend(vsk_Task * const self) {
    switch (self->_state) {
        case vsk_TaskState_running: {
            self->_state = vsk_TaskState_suspended;
        } break;
        case vsk_TaskState_suspended:
        case vsk_TaskState_ready:
        default: {
            // ignore
        } break;
    }
}
/*----------------------------------------------------------------------------*/
ctb_Node * vsk_Task_toNode(vsk_Task * const self) {
    return &self->_super.node;
}
