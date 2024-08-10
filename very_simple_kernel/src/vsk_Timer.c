/*----------------------------------------------------------------------------*/
#include "vsk_Timer.h"
/*----------------------------------------------------------------------------*/
#include "vsk_Assert.h"
#include "vsk_Time.h"
#include "vsk_TimerSupervisor.h"
/*----------------------------------------------------------------------------*/
vsk_Timer * vsk_Timer_init(
    vsk_Timer * const self,
    uint32_t const delayMillis,
    uint32_t const periodMillis,
    vsk_TimerCallback const callback,
    void * const obj
) {
    uint16_t const tickPeriodMillis = vsk_Time_getTickPeriodMillis(vsk_Time_());
    vsk_Assert_true(vsk_Assert_(), (delayMillis % tickPeriodMillis) == 0);
    vsk_Assert_true(vsk_Assert_(), (periodMillis % tickPeriodMillis) == 0);
    self->delayMillis = delayMillis;
    self->periodMillis = periodMillis;
    self->callback = callback;
    self->obj = obj;
    self->millisCountDown = 0;
    self->isRunning = false;
    vsk_TimerSupervisor_register(vsk_TimerSupervisor_(), self);
    return self;
}
/*----------------------------------------------------------------------------*/
// cppcheck-suppress unusedFunction // API function
void vsk_Timer_start(vsk_Timer * const self) {
    self->millisCountDown = self->delayMillis;
    self->isRunning = true;
}
/*----------------------------------------------------------------------------*/
// cppcheck-suppress unusedFunction // API function
void vsk_Timer_stop(vsk_Timer * const self) {
    self->isRunning = false;
    self->millisCountDown = 0;
}
/*----------------------------------------------------------------------------*/
// cppcheck-suppress unusedFunction // API function
bool vsk_Timer_isRunning(vsk_Timer * const self) {
    (void)self;
    return self->isRunning;
}
/*----------------------------------------------------------------------------*/
void vsk_Timer_onTick(vsk_Timer * const self) {
    if (self->isRunning) {
        uint16_t const tickPeriodMillis =
            vsk_Time_getTickPeriodMillis(vsk_Time_());
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
