#include "vsk_OnStartEvent.h"

vsk_OnStartEvent_t vsk_OnStartEvent;

vsk_OnStartEvent_t * vsk_OnStartEvent_init(vsk_OnStartEvent_t * const self) {
    vsk_Event_init((vsk_Event_t *)self);
    return self;
}
