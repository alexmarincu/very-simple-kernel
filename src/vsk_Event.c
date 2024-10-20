#include "vsk_Event.h"
#include "ctb.h"

vsk_Event_t * vsk_Event_init(vsk_Event_t * const self) {
    ctb_DList_init(&self->eventSubscriptions);
    return self;
}

static void publish(ctb_DNode_t * const evSubNode) {
    vsk_EventSubscription_t * const evSub = ctb_containerOf(
        evSubNode, vsk_EventSubscription_t, node
    );
    vsk_EventSubscription_publish(evSub);
}

void vsk_Event_raise(vsk_Event_t * const self) {
    ctb_DList_forEach(&self->eventSubscriptions, publish);
}

void vsk_Event_subscribe(
    vsk_Event_t * const self, vsk_EventSubscription_t * const subscription
) {
    ctb_DList_addFirst(&self->eventSubscriptions, (ctb_DNode_t *)subscription);
}
