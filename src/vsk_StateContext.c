#include "vsk_StateContext.h"
#include <stddef.h>

vsk_StateContext_t * vsk_StateContext_init(
    vsk_StateContext_t * const self, vsk_State_t * const initialState
) {
    self->state        = NULL;
    self->initialState = initialState;
    return self;
}

void vsk_StateContext_transition(
    vsk_StateContext_t * const self, vsk_State_t * const state
) {
    if (self->state != NULL) {
        vsk_State_onExit(self->state);
    }
    self->state = state;
    if (self->state != NULL) {
        vsk_State_onEnter(self->state);
    }
}
