/*----------------------------------------------------------------------------*/
#include "vsk_State.h"
/*----------------------------------------------------------------------------*/
static void vsk_State_onEnter_default(vsk_State * const self);
static void vsk_State_onExit_default(vsk_State * const self);
/*----------------------------------------------------------------------------*/
vsk_State * vsk_State_init(
    vsk_State * const self, vsk_StateContext * const stateContext
) {
    self->_stateContext = stateContext;
    self->_onEnter = vsk_State_onEnter_default;
    self->_onExit = vsk_State_onExit_default;
    return self;
}
/*----------------------------------------------------------------------------*/
static void vsk_State_onEnter_default(vsk_State * const self) {
    (void)self;
}
/*----------------------------------------------------------------------------*/
void vsk_State_onEnter(vsk_State * const self) {
    self->_onEnter(self);
}
/*----------------------------------------------------------------------------*/
static void vsk_State_onExit_default(vsk_State * const self) {
    (void)self;
}
/*----------------------------------------------------------------------------*/
void vsk_State_onExit(vsk_State * const self) {
    self->_onExit(self);
}
