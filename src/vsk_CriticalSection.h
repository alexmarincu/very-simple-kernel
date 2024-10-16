/**
 * @file
 */
#ifndef VSK_CRITICALSECTION_H
#define VSK_CRITICALSECTION_H

typedef struct vsk_CriticalSection vsk_CriticalSection_t;

#include <stdint.h>

typedef void (*vsk_CriticalSection_OnEnter_t)(void);

typedef void (*vsk_CriticalSection_OnExit_t)(void);

struct vsk_CriticalSection {
    vsk_CriticalSection_OnEnter_t onEnter;
    vsk_CriticalSection_OnExit_t  onExit;
    uint8_t volatile nestingLevels;
};

extern vsk_CriticalSection_t vsk_CriticalSection;

vsk_CriticalSection_t * vsk_CriticalSection_init(
    vsk_CriticalSection_t * const       self,
    vsk_CriticalSection_OnEnter_t const onEnter,
    vsk_CriticalSection_OnExit_t const  onExit
);

void vsk_CriticalSection_enter(vsk_CriticalSection_t * const self);

void vsk_CriticalSection_exit(vsk_CriticalSection_t * const self);

#endif // VSK_CRITICALSECTION_H
