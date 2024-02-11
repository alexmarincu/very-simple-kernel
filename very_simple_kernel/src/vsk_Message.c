/*----------------------------------------------------------------------------*/
#include "vsk_Message.h"
/*----------------------------------------------------------------------------*/
vsk_Message * vsk_Message_init(
    vsk_Message * const self,
    vsk_MessageHandler const handler,
    void * const obj
) {
    self->_handler = handler;
    self->_obj = obj;
    return self;
}
/*----------------------------------------------------------------------------*/
void vsk_Message_dispatch(vsk_Message * const self) {
    self->_handler(self->_obj);
}
