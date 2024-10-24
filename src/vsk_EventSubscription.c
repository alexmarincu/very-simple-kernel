#include "vsk_EventSubscription.h"

vsk_EventSubscription_t * vsk_EventSubscription_init(
    vsk_EventSubscription_t * const self,
    vsk_Inbox_t * const             inbox,
    vsk_Message_Handler_t const     handler,
    void * const                    obj
) {
    self->inbox = inbox;
    vsk_Message_init(&self->message, handler, obj);
    return self;
}

void vsk_EventSubscription_publish(vsk_EventSubscription_t * const self) {
    vsk_Inbox_postMessage(self->inbox, &self->message);
}
