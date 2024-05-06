/*----------------------------------------------------------------------------*/
#include "vsk_EventSubscription.h"
/*----------------------------------------------------------------------------*/
vsk_EventSubscription * vsk_EventSubscription_init(
    vsk_EventSubscription * const self,
    vsk_Inbox * const inbox,
    vsk_MessageHandler const handler,
    void * const obj
) {
    self->inbox = inbox;
    vsk_Message_init(&self->message, handler, obj);
    return self;
}
/*----------------------------------------------------------------------------*/
void vsk_EventSubscription_publish(vsk_EventSubscription * const self) {
    vsk_Inbox_postMessage(self->inbox, &self->message);
}
