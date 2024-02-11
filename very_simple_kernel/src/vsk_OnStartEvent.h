/*----------------------------------------------------------------------------*/
#ifndef VSK_ONSTARTEVENT_H
#define VSK_ONSTARTEVENT_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_OnStartEvent vsk_OnStartEvent;
/*----------------------------------------------------------------------------*/
#include "vsk_Event.h"
/*----------------------------------------------------------------------------*/
struct vsk_OnStartEvent {
    struct {
        vsk_Event event;
    } _super;
};
/*----------------------------------------------------------------------------*/
vsk_OnStartEvent * vsk_OnStartEvent_(void);
vsk_OnStartEvent * vsk_OnStartEvent_init(vsk_OnStartEvent * const self);
#endif // VSK_ONSTARTEVENT_H
