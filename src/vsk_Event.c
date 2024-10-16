#include "vsk_Event.h"

vsk_Event_t * vsk_Event_init(vsk_Event_t * const self) {
    ctb_DList_init(&self->eventSubscriptions);
    return self;
}

static void publish(vsk_EventSubscription_t * const subscription) {
    vsk_EventSubscription_publish(subscription);
}

void vsk_Event_raise(vsk_Event_t * const self) {
    ctb_DList_forEach(
        &self->eventSubscriptions,
        (ctb_DListIterator_ForEachOperation_t)publish
    );
}

void vsk_Event_subscribe(
    vsk_Event_t * const self, vsk_EventSubscription_t * const subscription
) {
    ctb_DList_addFirst(&self->eventSubscriptions, (ctb_DNode_t *)subscription);
}
