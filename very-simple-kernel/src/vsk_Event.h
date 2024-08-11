/*----------------------------------------------------------------------------*/
#ifndef VSK_EVENT_H
#define VSK_EVENT_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_Event vsk_Event;
/*----------------------------------------------------------------------------*/
#include "../../c-tool-box/c_tool_box/src/ctb_LinkedList.h"
#include "vsk_EventSubscription.h"
/*----------------------------------------------------------------------------*/
struct vsk_Event {
    ctb_LinkedList eventSubscriptions;
};
/*----------------------------------------------------------------------------*/
vsk_Event * vsk_Event_init(vsk_Event * const self);
void vsk_Event_raise(vsk_Event * const self);
void vsk_Event_subscribe(
    vsk_Event * const self, vsk_EventSubscription * const subscription
);

#endif // VSK_EVENT_H
