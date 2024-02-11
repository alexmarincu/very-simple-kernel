/*----------------------------------------------------------------------------*/
#ifndef VSK_STATE_H
#define VSK_STATE_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_State vsk_State;
/*----------------------------------------------------------------------------*/
#include <stdbool.h>
/*----------------------------------------------------------------------------*/
#include "vsk_StateContext.h"
/*----------------------------------------------------------------------------*/
typedef void (*vsk_StateOnEnter)(vsk_State * const self);
typedef void (*vsk_StateOnExit)(vsk_State * const self);
/*----------------------------------------------------------------------------*/
struct vsk_State {
    vsk_StateContext * _stateContext;
    vsk_StateOnEnter _onEnter;
    vsk_StateOnExit _onExit;
};
/*----------------------------------------------------------------------------*/
vsk_State * vsk_State_init(
    vsk_State * const self, vsk_StateContext * const stateContext
);
void vsk_State_onEnter(vsk_State * const self);
void vsk_State_onExit(vsk_State * const self);
#endif // VSK_STATE_H
