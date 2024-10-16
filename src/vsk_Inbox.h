/**
 * @file
 */
#ifndef VSK_INBOX_H
#define VSK_INBOX_H

typedef struct vsk_Inbox_Class vsk_Inbox_Class_t;

typedef struct vsk_Inbox vsk_Inbox_t;

#include "ctb_Queue.h"
#include "vsk_Message.h"
#include "vsk_Task.h"

struct vsk_Inbox_Class {
    ctb_DList_t inboxes;
};

struct vsk_Inbox {
    vsk_Inbox_Class_t * cls;
    ctb_DNode_t         node;
    vsk_Task_t *        task;
    ctb_Queue_t         messageQueue;
};

extern vsk_Inbox_Class_t vsk_Inbox_Class;

vsk_Inbox_Class_t * vsk_Inbox_Class_init(
    vsk_Inbox_Class_t * const cls
);

void vsk_Inbox_Class_onTick(vsk_Inbox_Class_t * const cls);

vsk_Inbox_t * vsk_Inbox_init(vsk_Inbox_t * const self, vsk_Task_t * const task);

bool vsk_Inbox_isEmpty(vsk_Inbox_t * const self);

void vsk_Inbox_postMessage(vsk_Inbox_t * const self, vsk_Message_t * const message);

vsk_Message_t * vsk_Inbox_readMessage(vsk_Inbox_t * const self);

void vsk_Inbox_clear(vsk_Inbox_t * const self);

void vsk_Inbox_onTick(vsk_Inbox_t * const self);

#endif // VSK_INBOX_H
