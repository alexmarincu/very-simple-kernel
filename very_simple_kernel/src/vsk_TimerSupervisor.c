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
    ctb_LinkedList_init(&self->timers);
    return self;
}
/*----------------------------------------------------------------------------*/
void vsk_TimerSupervisor_register(
    vsk_TimerSupervisor * const self, vsk_Timer * const timer
) {
    ctb_LinkedList_addLast(&self->timers, (ctb_Node *)timer);
}
/*----------------------------------------------------------------------------*/
static void vsk_onSysTick(vsk_Timer * const timer) {
    vsk_Timer_onSysTick(timer);
}
/*----------------------------------------------------------------------------*/
void vsk_TimerSupervisor_onSysTick(vsk_TimerSupervisor * const self) {
    ctb_LinkedList_forEach(
        &self->timers, (ctb_LinkedListIteratorForEachOperation)vsk_onSysTick
    );
}
