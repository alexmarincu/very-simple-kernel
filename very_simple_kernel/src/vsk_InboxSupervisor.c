/*----------------------------------------------------------------------------*/
#include "vsk_InboxSupervisor.h"
/*----------------------------------------------------------------------------*/
vsk_InboxSupervisor * vsk_InboxSupervisor_(void) {
    static vsk_InboxSupervisor self;
    return &self;
}
/*----------------------------------------------------------------------------*/
vsk_InboxSupervisor * vsk_InboxSupervisor_init(
    vsk_InboxSupervisor * const self
) {
    ctb_LinkedList_init(&self->_inboxes);
    return self;
}
/*----------------------------------------------------------------------------*/
void vsk_InboxSupervisor_register(
    vsk_InboxSupervisor * const self, vsk_Inbox * const inbox
) {
    ctb_LinkedList_addLast(&self->_inboxes, (ctb_Node *)inbox);
}
/*----------------------------------------------------------------------------*/
static void vsk_onSysTick(vsk_Inbox * const inbox) {
    vsk_Inbox_onSysTick(inbox);
}
/*----------------------------------------------------------------------------*/
void vsk_InboxSupervisor_onSysTick(vsk_InboxSupervisor * const self) {
    ctb_LinkedList_forEach(
        &self->_inboxes, (ctb_LinkedListIteratorForEachOperation)vsk_onSysTick
    );
}
