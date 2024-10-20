/*----------------------------------------------------------------------------*/
#ifndef VSK_MESSAGE_H
#define VSK_MESSAGE_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_Message vsk_Message;
/*----------------------------------------------------------------------------*/
#include "ctb_DNode.h"
typedef void (*vsk_MessageHandler)(void * const obj);
/*----------------------------------------------------------------------------*/
struct vsk_Message {
    ctb_DNode_t        node;
    vsk_MessageHandler handler;
    void *             obj;
};
/*----------------------------------------------------------------------------*/
vsk_Message * vsk_Message_init(
    vsk_Message * const      self,
    vsk_MessageHandler const handler,
    void * const             obj
);
void vsk_Message_dispatch(vsk_Message * const self);
#endif // VSK_MESSAGE_H
