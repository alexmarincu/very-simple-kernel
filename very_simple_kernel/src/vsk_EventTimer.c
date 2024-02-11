/*----------------------------------------------------------------------------*/
#include "vsk_EventTimer.h"
/*----------------------------------------------------------------------------*/
static void vsk_raiseEvent(vsk_EventTimer * const self) {
    vsk_Event_raise(self->_event);
}
/*----------------------------------------------------------------------------*/
vsk_EventTimer * vsk_EventTimer_init(
    vsk_EventTimer * const self,
    uint32_t const delayMillis,
    uint32_t const periodMillis,
    vsk_Event * const event
) {
    vsk_Timer_init(
        (vsk_Timer *)self, delayMillis, periodMillis,
        (vsk_TimerCallback)vsk_raiseEvent, self
    );
    self->_event = event;
    return self;
}
