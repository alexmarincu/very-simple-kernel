/**
 * @file
 */
#ifndef VSK_EVENTSUBSCRIPTION_H
#define VSK_EVENTSUBSCRIPTION_H

typedef struct vsk_EventSubscription vsk_EventSubscription_t;

#include "vsk_Inbox.h"
#include "vsk_Message.h"

struct vsk_EventSubscription {
    ctb_DNode_t   node;
    vsk_Inbox_t * inbox;
    vsk_Message_t message;
};

vsk_EventSubscription_t * vsk_EventSubscription_init(
    vsk_EventSubscription_t * const self,
    vsk_Inbox_t * const             inbox,
    vsk_Message_Handler_t const     handler,
    void * const                    obj
);

void vsk_EventSubscription_publish(vsk_EventSubscription_t * const self);

#endif // VSK_EVENTSUBSCRIPTION_H
