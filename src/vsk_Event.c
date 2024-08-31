/*----------------------------------------------------------------------------*/
#include "vsk_Event.h"
/*----------------------------------------------------------------------------*/
vsk_Event * vsk_Event_init(vsk_Event * const self) {
    ctb_DList_init(&self->eventSubscriptions);
    return self;
}
/*----------------------------------------------------------------------------*/
static void vsk_publish(vsk_EventSubscription * const subscription) {
    vsk_EventSubscription_publish(subscription);
}
/*----------------------------------------------------------------------------*/
void vsk_Event_raise(vsk_Event * const self) {
    ctb_DList_forEach(
        &self->eventSubscriptions,
        (ctb_DListIterator_ForEachOperation_t)vsk_publish
    );
}
/*----------------------------------------------------------------------------*/
void vsk_Event_subscribe(
    vsk_Event * const self, vsk_EventSubscription * const subscription
) {
    ctb_DList_addFirst(&self->eventSubscriptions, (ctb_DNode_t *)subscription);
}
