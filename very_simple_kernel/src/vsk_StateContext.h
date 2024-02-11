/*----------------------------------------------------------------------------*/
#ifndef VSK_STATECONTEXT_H
#define VSK_STATECONTEXT_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_StateContext vsk_StateContext;
/*----------------------------------------------------------------------------*/
#include "vsk_State.h"
/*----------------------------------------------------------------------------*/
struct vsk_StateContext {
    vsk_State * _state;
    vsk_State * _initialState;
};
/*----------------------------------------------------------------------------*/
vsk_StateContext * vsk_StateContext_init(
    vsk_StateContext * const self, vsk_State * const initialState
);
void vsk_StateContext_transition(
    vsk_StateContext * const self, vsk_State * const state
);
#endif // VSK_STATECONTEXT_H
