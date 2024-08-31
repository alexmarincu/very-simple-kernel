/*----------------------------------------------------------------------------*/
#include "vsk_StateContext.h"
/*----------------------------------------------------------------------------*/
#include <stddef.h>
/*----------------------------------------------------------------------------*/
vsk_StateContext * vsk_StateContext_init(
    vsk_StateContext * const self, vsk_State * const initialState
) {
    self->state        = NULL;
    self->initialState = initialState;
    return self;
}
/*----------------------------------------------------------------------------*/
void vsk_StateContext_transition(
    vsk_StateContext * const self, vsk_State * const state
) {
    if (self->state != NULL) {
        vsk_State_onExit(self->state);
    }
    self->state = state;
    if (self->state != NULL) {
        vsk_State_onEnter(self->state);
    }
}
