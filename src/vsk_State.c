#include "vsk_State.h"

static void onEnter_default(vsk_State_t * const self);
static void onExit_default(vsk_State_t * const self);

// cppcheck-suppress unusedFunction // API function
vsk_State_t * vsk_State_init(
    vsk_State_t * const self, vsk_StateContext_t * const stateContext
) {
    self->stateContext = stateContext;
    self->onEnter      = onEnter_default;
    self->onExit       = onExit_default;
    return self;
}

static void onEnter_default(vsk_State_t * const self) {
    (void)self;
}

void vsk_State_onEnter(vsk_State_t * const self) {
    self->onEnter(self);
}

static void onExit_default(vsk_State_t * const self) {
    (void)self;
}

void vsk_State_onExit(vsk_State_t * const self) {
    self->onExit(self);
}
