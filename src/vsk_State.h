/**
 * @file
 */
#ifndef VSK_STATE_H
#define VSK_STATE_H

typedef struct vsk_State vsk_State_t;

#include "vsk_StateContext.h"
#include <stdbool.h>

typedef void (*vsk_State_OnEnter_t)(vsk_State_t * const self);

typedef void (*vsk_State_OnExit_t)(vsk_State_t * const self);

struct vsk_State {
    vsk_StateContext_t * stateContext;
    vsk_State_OnEnter_t  onEnter;
    vsk_State_OnExit_t   onExit;
};

vsk_State_t * vsk_State_init(
    vsk_State_t * const self, vsk_StateContext_t * const stateContext
);

void vsk_State_onEnter(vsk_State_t * const self);

void vsk_State_onExit(vsk_State_t * const self);

#endif // VSK_STATE_H
