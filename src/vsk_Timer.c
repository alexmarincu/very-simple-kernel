#include "vsk_Timer.h"
#include "ctb.h"
#include "vsk_Assert.h"
#include "vsk_Time.h"

vsk_Timer_Class_t vsk_Timer_Class;

static void registerTimer(
    vsk_Timer_Class_t * const cls, vsk_Timer_t * const timer
);
static void onTick(vsk_Timer_t * const self);

vsk_Timer_Class_t * vsk_Timer_Class_init(
    vsk_Timer_Class_t * const cls
) {
    ctb_DList_init(&cls->timers);
    return cls;
}

static void registerTimer(
    vsk_Timer_Class_t * const cls, vsk_Timer_t * const timer
) {
    ctb_DList_addLast(&cls->timers, (ctb_DNode_t *)&timer->node);
}

static void onTimerTick(ctb_DNode_t * const timerNode) {
    vsk_Timer_t * const timer = ctb_containerOf(timerNode, vsk_Timer_t, node);
    onTick(timer);
}

void vsk_Timer_Class_onTick(vsk_Timer_Class_t * const cls) {
    ctb_DList_forEach(&cls->timers, onTimerTick);
}

vsk_Timer_t * vsk_Timer_init(
    vsk_Timer_t * const        self,
    uint32_t const             delayMillis,
    uint32_t const             periodMillis,
    vsk_Timer_Callback_t const callback,
    void * const               obj
) {
    self->cls = &vsk_Timer_Class;
    ctb_DNode_init(&self->node);
    uint16_t const tickPeriodMillis = vsk_Time_getTickPeriodMillis(&vsk_Time);
    vsk_Assert_true(&vsk_Assert, (delayMillis % tickPeriodMillis) == 0);
    vsk_Assert_true(&vsk_Assert, (periodMillis % tickPeriodMillis) == 0);
    self->delayMillis     = delayMillis;
    self->periodMillis    = periodMillis;
    self->callback        = callback;
    self->obj             = obj;
    self->millisCountDown = 0;
    self->isRunning       = false;
    registerTimer(&vsk_Timer_Class, self);
    return self;
}

// cppcheck-suppress unusedFunction // API function
void vsk_Timer_start(vsk_Timer_t * const self) {
    self->millisCountDown = self->delayMillis;
    self->isRunning       = true;
}

// cppcheck-suppress unusedFunction // API function
void vsk_Timer_stop(vsk_Timer_t * const self) {
    self->isRunning       = false;
    self->millisCountDown = 0;
}

// cppcheck-suppress unusedFunction // API function
bool vsk_Timer_isRunning(vsk_Timer_t * const self) {
    (void)self;
    return self->isRunning;
}

static void onTick(vsk_Timer_t * const self) {
    if (self->isRunning) {
        uint16_t const tickPeriodMillis =
            vsk_Time_getTickPeriodMillis(&vsk_Time);
        if (self->millisCountDown > 0) {
            self->millisCountDown -= tickPeriodMillis;
        }
        if (self->millisCountDown == 0) {
            if (self->periodMillis > 0) {
                self->millisCountDown = self->periodMillis;
            } else {
                self->isRunning = false;
            }
            if (self->callback != NULL) {
                self->callback(self->obj);
            }
        }
    }
}
