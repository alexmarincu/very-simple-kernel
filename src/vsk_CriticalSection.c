#include "vsk_CriticalSection.h"

vsk_CriticalSection_t vsk_CriticalSection;

vsk_CriticalSection_t * vsk_CriticalSection_init(
    vsk_CriticalSection_t * const       self,
    vsk_CriticalSection_OnEnter_t const onEnter,
    vsk_CriticalSection_OnExit_t const  onExit
) {
    self->onEnter       = onEnter;
    self->onExit        = onExit;
    self->nestingLevels = 0;
    return self;
}

void vsk_CriticalSection_enter(vsk_CriticalSection_t * const self) {
    self->onEnter();
    self->nestingLevels++;
}

void vsk_CriticalSection_exit(vsk_CriticalSection_t * const self) {
    if (self->nestingLevels > 0) {
        self->nestingLevels--;
        if (self->nestingLevels == 0) {
            self->onExit();
        }
    }
}
