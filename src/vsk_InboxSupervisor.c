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
    ctb_DList_init(&self->inboxes);
    return self;
}
/*----------------------------------------------------------------------------*/
void vsk_InboxSupervisor_register(
    vsk_InboxSupervisor * const self, vsk_Inbox * const inbox
) {
    ctb_DList_addLast(&self->inboxes, (ctb_DNode_t *)inbox);
}
/*----------------------------------------------------------------------------*/
static void vsk_onTick(vsk_Inbox * const inbox) {
    vsk_Inbox_onTick(inbox);
}
/*----------------------------------------------------------------------------*/
void vsk_InboxSupervisor_onTick(vsk_InboxSupervisor * const self) {
    ctb_DList_forEach(
        &self->inboxes, (ctb_DListIterator_ForEachOperation_t)vsk_onTick
    );
}
