#include "vsk_Message.h"

vsk_Message_t * vsk_Message_init(
    vsk_Message_t * const       self,
    vsk_Message_Handler_t const handler,
    void * const                obj
) {
    self->handler = handler;
    self->obj     = obj;
    return self;
}

void vsk_Message_dispatch(vsk_Message_t * const self) {
    self->handler(self->obj);
}
