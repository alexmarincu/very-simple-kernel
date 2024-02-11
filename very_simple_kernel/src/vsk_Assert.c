/*----------------------------------------------------------------------------*/
#include "vsk_Assert.h"
/*----------------------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>
/*----------------------------------------------------------------------------*/
vsk_Assert * vsk_Assert_(void) {
    static vsk_Assert self;
    return &self;
}
/*----------------------------------------------------------------------------*/
vsk_Assert * vsk_Assert_init(
    vsk_Assert * const self, vsk_AssertOnFail const onFail
) {
    self->_onFail = onFail;
    return self;
}
/*----------------------------------------------------------------------------*/
void vsk_Assert_true(vsk_Assert * const self, bool const condition) {
    if (condition == false) {
        vsk_Assert_fail(self);
    }
}
/*----------------------------------------------------------------------------*/
void vsk_Assert_fail(vsk_Assert * const self) {
    self->_onFail();
}
