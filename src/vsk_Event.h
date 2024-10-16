/**
 * @file
 */
#ifndef VSK_EVENT_H
#define VSK_EVENT_H

typedef struct vsk_Event vsk_Event_t;

#include "ctb_DList.h"
#include "vsk_EventSubscription.h"

struct vsk_Event {
    ctb_DList_t eventSubscriptions;
};

vsk_Event_t * vsk_Event_init(vsk_Event_t * const self);

void vsk_Event_raise(vsk_Event_t * const self);

void vsk_Event_subscribe(
    vsk_Event_t * const self, vsk_EventSubscription_t * const subscription
);

#endif // VSK_EVENT_H
