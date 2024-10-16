/**
 * @file
 */
#ifndef VSK_ONSTARTEVENT_H
#define VSK_ONSTARTEVENT_H

typedef struct vsk_OnStartEvent vsk_OnStartEvent_t;

#include "vsk_Event.h"

struct vsk_OnStartEvent {
    vsk_Event_t event;
};

extern vsk_OnStartEvent_t vsk_OnStartEvent;

vsk_OnStartEvent_t * vsk_OnStartEvent_init(vsk_OnStartEvent_t * const self);

#endif // VSK_ONSTARTEVENT_H
