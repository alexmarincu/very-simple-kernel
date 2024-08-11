/*----------------------------------------------------------------------------*/
#include "vsk_State.h"
/*----------------------------------------------------------------------------*/
static void vsk_State_onEnter_default(vsk_State * const self);
static void vsk_State_onExit_default(vsk_State * const self);
/*----------------------------------------------------------------------------*/
// cppcheck-suppress unusedFunction // API function
vsk_State * vsk_State_init(
    vsk_State * const self, vsk_StateContext * const stateContext
) {
    self->stateContext = stateContext;
    self->onEnter = vsk_State_onEnter_default;
    self->onExit = vsk_State_onExit_default;
    return self;
}
/*----------------------------------------------------------------------------*/
static void vsk_State_onEnter_default(vsk_State * const self) {
    (void)self;
}
/*----------------------------------------------------------------------------*/
void vsk_State_onEnter(vsk_State * const self) {
    self->onEnter(self);
}
/*----------------------------------------------------------------------------*/
static void vsk_State_onExit_default(vsk_State * const self) {
    (void)self;
}
/*----------------------------------------------------------------------------*/
void vsk_State_onExit(vsk_State * const self) {
    self->onExit(self);
}
