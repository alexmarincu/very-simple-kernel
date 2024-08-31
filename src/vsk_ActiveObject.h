/*----------------------------------------------------------------------------*/
#ifndef VSK_ACTIVEOBJECT_H
#define VSK_ACTIVEOBJECT_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_ActiveObject vsk_ActiveObject;
/*----------------------------------------------------------------------------*/
#include "vsk_EventSubscription.h"
#include "vsk_StateContext.h"
#include "vsk_Task.h"
/*----------------------------------------------------------------------------*/
struct vsk_ActiveObject {
    vsk_StateContext stateContext;
    vsk_Task         task;
    vsk_Inbox        inbox;
    struct {
        vsk_EventSubscription onStart;
    } eventSubscriptions;
};
/*----------------------------------------------------------------------------*/
vsk_ActiveObject * vsk_ActiveObject_init(
    vsk_ActiveObject * const self, vsk_State * const initialState
);
#endif // VSK_ACTIVEOBJECT_H
