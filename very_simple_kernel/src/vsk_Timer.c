/*----------------------------------------------------------------------------*/
#include "vsk_Timer.h"
/*----------------------------------------------------------------------------*/
#include "vsk_Assert.h"
#include "vsk_Time.h"
/*----------------------------------------------------------------------------*/
vsk_Timer * vsk_Timer_init(
    vsk_Timer * const self,
    uint32_t const delayMillis,
    uint32_t const periodMillis,
    vsk_TimerCallback const callback,
    void * const obj
) {
    uint16_t const tickPeriodMillis =
        vsk_Time_getTickPeriodMillis(vsk_Time_());
    vsk_Assert_true(vsk_Assert_(), (delayMillis % tickPeriodMillis) == 0);
    vsk_Assert_true(vsk_Assert_(), (periodMillis % tickPeriodMillis) == 0);
    self->_delayMillis = delayMillis;
    self->_periodMillis = periodMillis;
    self->_callback = callback;
    self->_obj = obj;
    self->_millisCountDown = 0;
    self->_isRunning = false;
    vsk_TimerSupervisor_register(vsk_TimerSupervisor_(), self);
    return self;
}
/*----------------------------------------------------------------------------*/
void vsk_Timer_start(vsk_Timer * const self) {
    self->_millisCountDown = self->_delayMillis;
    self->_isRunning = true;
}
/*----------------------------------------------------------------------------*/
void vsk_Timer_stop(vsk_Timer * const self) {
    self->_isRunning = false;
    self->_millisCountDown = 0;
}
/*----------------------------------------------------------------------------*/
bool vsk_Timer_isRunning(vsk_Timer * const self) {
    return self->_isRunning;
}
/*----------------------------------------------------------------------------*/
void vsk_Timer_onSysTick(vsk_Timer * const self) {
    if (self->_isRunning) {
        uint16_t const tickPeriodMillis =
            vsk_Time_getTickPeriodMillis(vsk_Time_());
        if (self->_millisCountDown > 0) {
            self->_millisCountDown -= tickPeriodMillis;
        }
        if (self->_millisCountDown == 0) {
            if (self->_periodMillis > 0) {
                self->_millisCountDown = self->_periodMillis;
            } else {
                self->_isRunning = false;
            }
            if (self->_callback != NULL) {
                self->_callback(self->_obj);
            }
        }
    }
}
