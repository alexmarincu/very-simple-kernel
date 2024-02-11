/*----------------------------------------------------------------------------*/
#include "vsk_Event.h"
/*----------------------------------------------------------------------------*/
vsk_Event * vsk_Event_init(vsk_Event * const self) {
    ctb_LinkedList_init(&self->_eventSubscriptions);
    return self;
}
/*----------------------------------------------------------------------------*/
static void vsk_publish(vsk_EventSubscription * const subscription) {
    vsk_EventSubscription_publish(subscription);
}
/*----------------------------------------------------------------------------*/
void vsk_Event_raise(vsk_Event * const self) {
    ctb_LinkedList_forEach(
        &self->_eventSubscriptions,
        (ctb_LinkedListIteratorForEachOperation)vsk_publish
    );
}
/*----------------------------------------------------------------------------*/
void vsk_Event_subscribe(
    vsk_Event * const self, vsk_EventSubscription * const subscription
) {
    ctb_LinkedList_addFirst(&self->_eventSubscriptions, (ctb_Node *)subscription);
}
