#include "vsk_Assert.h"

vsk_Assert_t vsk_Assert;

vsk_Assert_t * vsk_Assert_init(
    vsk_Assert_t * const self, vsk_Assert_OnFail_t const onFail
) {
    self->onFail = onFail;
    return self;
}

void vsk_Assert_true(vsk_Assert_t * const self, bool const condition) {
    if (condition == false) {
        vsk_Assert_fail(self);
    }
}

void vsk_Assert_fail(vsk_Assert_t * const self) {
    self->onFail();
}
