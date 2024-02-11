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
    struct {
        ctb_Node node;
    } _super;
    vsk_Inbox * _inbox;
    vsk_Message _message;
};
/*----------------------------------------------------------------------------*/
vsk_EventSubscription * vsk_EventSubscription_init(
    vsk_EventSubscription * const self,
    vsk_Inbox * const inbox,
    vsk_MessageHandler const handler,
    void * const obj
);
void vsk_EventSubscription_publish(vsk_EventSubscription * const self);
#endif // VSK_EVENTSUBSCRIPTION_H
