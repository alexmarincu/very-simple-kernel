/*----------------------------------------------------------------------------*/
#ifndef VSK_EVENTSUBSCRIPTION_H
#define VSK_EVENTSUBSCRIPTION_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_EventSubscription vsk_EventSubscription;
/*----------------------------------------------------------------------------*/
#include "vsk_Inbox.h"
#include "vsk_Message.h"
/*----------------------------------------------------------------------------*/
struct vsk_EventSubscription {
    ctb_DNode_t node;
    vsk_Inbox * inbox;
    vsk_Message message;
};
/*----------------------------------------------------------------------------*/
vsk_EventSubscription * vsk_EventSubscription_init(
    vsk_EventSubscription * const self,
    vsk_Inbox * const             inbox,
    vsk_MessageHandler const      handler,
    void * const                  obj
);
void vsk_EventSubscription_publish(vsk_EventSubscription * const self);
#endif // VSK_EVENTSUBSCRIPTION_H
