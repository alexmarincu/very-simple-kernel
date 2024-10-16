/**
 * @file
 */
#ifndef VSK_ACTIVEOBJECT_H
#define VSK_ACTIVEOBJECT_H

typedef struct vsk_ActiveObject vsk_ActiveObject_t;

#include "vsk_EventSubscription.h"
#include "vsk_StateContext.h"
#include "vsk_Task.h"

struct vsk_ActiveObject {
    vsk_StateContext_t stateContext;
    vsk_Task_t         task;
    vsk_Inbox_t        inbox;
    struct {
        vsk_EventSubscription_t onStart;
    } eventSubscriptions;
};

vsk_ActiveObject_t * vsk_ActiveObject_init(
    vsk_ActiveObject_t * const self, vsk_State_t * const initialState
);

#endif // VSK_ACTIVEOBJECT_H
