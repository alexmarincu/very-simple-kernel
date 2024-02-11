/*----------------------------------------------------------------------------*/
#include "vsk_OnStartEvent.h"
/*----------------------------------------------------------------------------*/
vsk_OnStartEvent * vsk_OnStartEvent_(void) {
    static vsk_OnStartEvent self;
    return &self;
}
/*----------------------------------------------------------------------------*/
vsk_OnStartEvent * vsk_OnStartEvent_init(vsk_OnStartEvent * const self) {
    vsk_Event_init((vsk_Event *)self);
    return self;
}
