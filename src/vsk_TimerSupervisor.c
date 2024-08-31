/*----------------------------------------------------------------------------*/
#include "vsk_TimerSupervisor.h"
/*----------------------------------------------------------------------------*/
vsk_TimerSupervisor * vsk_TimerSupervisor_(void) {
    static vsk_TimerSupervisor self;
    return &self;
}
/*----------------------------------------------------------------------------*/
vsk_TimerSupervisor * vsk_TimerSupervisor_init(
    vsk_TimerSupervisor * const self
) {
    ctb_DList_init(&self->timers);
    return self;
}
/*----------------------------------------------------------------------------*/
void vsk_TimerSupervisor_register(
    vsk_TimerSupervisor * const self, vsk_Timer * const timer
) {
    ctb_DList_addLast(&self->timers, (ctb_DNode_t *)timer);
}
/*----------------------------------------------------------------------------*/
static void vsk_onTick(vsk_Timer * const timer) {
    vsk_Timer_onTick(timer);
}
/*----------------------------------------------------------------------------*/
void vsk_TimerSupervisor_onTick(vsk_TimerSupervisor * const self) {
    ctb_DList_forEach(
        &self->timers, (ctb_DListIterator_ForEachOperation_t)vsk_onTick
    );
}
