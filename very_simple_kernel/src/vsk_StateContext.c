/*----------------------------------------------------------------------------*/
#include "vsk_StateContext.h"
/*----------------------------------------------------------------------------*/
#include <stddef.h>
/*----------------------------------------------------------------------------*/
vsk_StateContext * vsk_StateContext_init(
    vsk_StateContext * const self, vsk_State * const initialState
) {
    self->_state = NULL;
    self->_initialState = initialState;
    return self;
}
/*----------------------------------------------------------------------------*/
void vsk_StateContext_transition(
    vsk_StateContext * const self, vsk_State * const state
) {
    if (self->_state != NULL) {
        vsk_State_onExit(self->_state);
    }
    self->_state = state;
    if (self->_state != NULL) {
        vsk_State_onEnter(self->_state);
    }
}
