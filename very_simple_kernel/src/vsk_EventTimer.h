/*----------------------------------------------------------------------------*/
#ifndef VSK_EVENTTIMER_H
#define VSK_EVENTTIMER_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_EventTimer vsk_EventTimer;
/*----------------------------------------------------------------------------*/
#include "vsk_Event.h"
#include "vsk_Timer.h"
/*----------------------------------------------------------------------------*/
struct vsk_EventTimer {
    struct {
        vsk_Timer timer;
    } _super;
    vsk_Event * _event;
};
/*----------------------------------------------------------------------------*/
vsk_EventTimer * vsk_EventTimer_init(
    vsk_EventTimer * const self,
    uint32_t const delayMillis,
    uint32_t const periodMillis,
    vsk_Event * const event
);
#endif // VSK_EVENTTIMER_H
