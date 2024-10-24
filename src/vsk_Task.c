#include "vsk_Task.h"
#include "ctb.h"
#include "vsk_OnStartEvent.h"
#include "vsk_Time.h"

vsk_Task_Class_t vsk_Task_Class;

static void registerTask(
    vsk_Task_Class_t * const cls, vsk_Task_t * const task
);
static void run(vsk_Task_t * const self);
static bool isReady(vsk_Task_t const * const self);

vsk_Task_Class_t * vsk_Task_Class_init(
    vsk_Task_Class_t * const       cls,
    vsk_Task_Class_OnStart_t const onStart,
    vsk_Task_Class_OnIdle_t const  onIdle
) {
    ctb_DList_init(&cls->tasks);
    cls->onStart = onStart;
    cls->onIdle  = onIdle;
    return cls;
}

static bool isTaskReady(ctb_DNode_t * const taskNode) {
    vsk_Task_t const * const task = ctb_containerOf(taskNode, vsk_Task_t, node);
    return isReady(task);
}

void vsk_Task_Class_startScheduler(vsk_Task_Class_t * const cls) {
    cls->onStart();
    vsk_Event_raise((vsk_Event_t *)&vsk_OnStartEvent);
    while (1) {
        ctb_DNode_t * const readyTaskNode = ctb_DList_find(
            &cls->tasks, isTaskReady
        );
        if (readyTaskNode) {
            vsk_Task_t * const readyTask = ctb_containerOf(
                readyTaskNode, vsk_Task_t, node
            );
            run(readyTask);
        } else {
            cls->onIdle();
        }
    }
}

static void registerTask(
    vsk_Task_Class_t * const cls, vsk_Task_t * const task
) {
    ctb_DList_addLast(&cls->tasks, &task->node);
}

vsk_Task_t * vsk_Task_init(
    vsk_Task_t * const self, vsk_Task_Operation_t const operation, void * const obj
) {
    self->cls = &vsk_Task_Class;
    ctb_DNode_init(&self->node);
    self->operation           = operation;
    self->obj                 = obj;
    self->state               = vsk_Task_State_suspended;
    self->lastStartTimeMillis = 0;
    self->maxRunTimeMillis    = 0;
    self->minPeriodMillis     = UINT32_MAX;
    self->cpuLoad             = 0;
    registerTask(&vsk_Task_Class, self);
    return self;
}

static bool isReady(vsk_Task_t const * const self) {
    return self->state == vsk_Task_State_ready;
}

static void profilingBefore(vsk_Task_t * const self) {
    uint32_t const startTimeMillis = vsk_Time_getMillisCount(&vsk_Time);
    uint32_t const periodMillis    = startTimeMillis - self->lastStartTimeMillis;
    if (periodMillis < self->minPeriodMillis) {
        self->minPeriodMillis = periodMillis;
    }
    self->cpuLoad             = (self->maxRunTimeMillis * 100) / self->minPeriodMillis;
    self->lastStartTimeMillis = startTimeMillis;
}

static void profilingAfter(vsk_Task_t * const self) {
    uint32_t const runTimeMillis =
        vsk_Time_getMillisCount(&vsk_Time) - self->lastStartTimeMillis;
    if (runTimeMillis > self->maxRunTimeMillis) {
        self->maxRunTimeMillis = runTimeMillis;
    }
}

static void run(vsk_Task_t * const self) {
    switch (self->state) {
        case vsk_Task_State_ready: {
            self->state = vsk_Task_State_running;
            profilingBefore(self);
            self->operation(self->obj);
            profilingAfter(self);
            self->state = vsk_Task_State_suspended;
        } break;
        case vsk_Task_State_suspended:
        case vsk_Task_State_running:
        default: {
            // ignore
        } break;
    }
}

void vsk_Task_activate(vsk_Task_t * const self) {
    switch (self->state) {
        case vsk_Task_State_suspended: {
            self->state = vsk_Task_State_ready;
        } break;
        case vsk_Task_State_ready:
        case vsk_Task_State_running:
        default: {
            // ignore
        } break;
    }
}

// cppcheck-suppress unusedFunction // API function
void vsk_Task_suspend(vsk_Task_t * const self) {
    switch (self->state) {
        case vsk_Task_State_running: {
            self->state = vsk_Task_State_suspended;
        } break;
        case vsk_Task_State_suspended:
        case vsk_Task_State_ready:
        default: {
            // ignore
        } break;
    }
}
