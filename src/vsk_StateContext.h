/**
 * @file
 */
#ifndef VSK_STATECONTEXT_H
#define VSK_STATECONTEXT_H

typedef struct vsk_StateContext vsk_StateContext_t;

#include "vsk_State.h"

struct vsk_StateContext {
    vsk_State_t * state;
    vsk_State_t * initialState;
};

vsk_StateContext_t * vsk_StateContext_init(
    vsk_StateContext_t * const self, vsk_State_t * const initialState
);

void vsk_StateContext_transition(
    vsk_StateContext_t * const self, vsk_State_t * const state
);

#endif // VSK_STATECONTEXT_H
