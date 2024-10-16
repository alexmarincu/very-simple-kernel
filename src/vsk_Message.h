/**
 * @file
 */
#ifndef VSK_MESSAGE_H
#define VSK_MESSAGE_H

typedef struct vsk_Message vsk_Message_t;

#include "ctb_DNode.h"

typedef void (*vsk_Message_Handler_t)(void * const obj);

struct vsk_Message {
    ctb_DNode_t           node;
    vsk_Message_Handler_t handler;
    void *                obj;
};

vsk_Message_t * vsk_Message_init(
    vsk_Message_t * const       self,
    vsk_Message_Handler_t const handler,
    void * const                obj
);

void vsk_Message_dispatch(vsk_Message_t * const self);

#endif // VSK_MESSAGE_H
