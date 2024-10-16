/**
 * @file
 */
#ifndef VSK_EVENTTIMER_H
#define VSK_EVENTTIMER_H

typedef struct vsk_EventTimer vsk_EventTimer_t;

#include "vsk_Event.h"
#include "vsk_Timer.h"

struct vsk_EventTimer {
    vsk_Timer_t   timer;
    vsk_Event_t * event;
};

vsk_EventTimer_t * vsk_EventTimer_init(
    vsk_EventTimer_t * const self,
    uint32_t const           delayMillis,
    uint32_t const           periodMillis,
    vsk_Event_t * const      event
);

#endif // VSK_EVENTTIMER_H
