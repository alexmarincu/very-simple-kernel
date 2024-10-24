#include "vsk_EventTimer.h"

static void raiseEvent(vsk_EventTimer_t * const self) {
    vsk_Event_raise(self->event);
}

// cppcheck-suppress unusedFunction // API function
vsk_EventTimer_t * vsk_EventTimer_init(
    vsk_EventTimer_t * const self,
    uint32_t const           delayMillis,
    uint32_t const           periodMillis,
    vsk_Event_t * const      event
) {
    vsk_Timer_init(
        (vsk_Timer_t *)self, delayMillis, periodMillis,
        (vsk_Timer_Callback_t)raiseEvent, self
    );
    self->event = event;
    return self;
}
