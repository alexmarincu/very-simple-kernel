/*----------------------------------------------------------------------------*/
#include "vsk_CriticalSection.h"
/*----------------------------------------------------------------------------*/
vsk_CriticalSection * vsk_CriticalSection_(void) {
    static vsk_CriticalSection self;
    return &self;
}
/*----------------------------------------------------------------------------*/
vsk_CriticalSection * vsk_CriticalSection_init(
    vsk_CriticalSection * const self,
    vsk_CriticalSectionOnEnter const onEnter,
    vsk_CriticalSectionOnExit const onExit
) {
    self->onEnter = onEnter;
    self->onExit = onExit;
    self->nestingLevels = 0;
    return self;
}
/*----------------------------------------------------------------------------*/
void vsk_CriticalSection_enter(vsk_CriticalSection * const self) {
    self->onEnter();
    self->nestingLevels++;
}
/*----------------------------------------------------------------------------*/
void vsk_CriticalSection_exit(vsk_CriticalSection * const self) {
    if (self->nestingLevels > 0) {
        self->nestingLevels--;
        if (self->nestingLevels == 0) {
            self->onExit();
        }
    }
}
