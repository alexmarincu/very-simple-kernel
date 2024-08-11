/*----------------------------------------------------------------------------*/
#include "vsk_Message.h"
/*----------------------------------------------------------------------------*/
vsk_Message * vsk_Message_init(
    vsk_Message * const self,
    vsk_MessageHandler const handler,
    void * const obj
) {
    self->handler = handler;
    self->obj = obj;
    return self;
}
/*----------------------------------------------------------------------------*/
void vsk_Message_dispatch(vsk_Message * const self) {
    self->handler(self->obj);
}
