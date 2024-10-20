#include "vsk_Inbox.h"
#include "ctb.h"
#include "vsk_CriticalSection.h"

vsk_Inbox_Class_t vsk_Inbox_Class;

static void registerInbox(
    vsk_Inbox_Class_t * const cls, vsk_Inbox_t * const inbox
);

vsk_Inbox_Class_t * vsk_Inbox_Class_init(
    vsk_Inbox_Class_t * const cls
) {
    ctb_DList_init(&cls->inboxes);
    return cls;
}

static void registerInbox(
    vsk_Inbox_Class_t * const cls, vsk_Inbox_t * const inbox
) {
    ctb_DList_addLast(&cls->inboxes, (ctb_DNode_t *)&inbox->node);
}

static void onTick(ctb_DNode_t * const inboxNode) {
    vsk_Inbox_t * const inbox = ctb_containerOf(inboxNode, vsk_Inbox_t, node);
    vsk_Inbox_onTick(inbox);
}

void vsk_Inbox_Class_onTick(vsk_Inbox_Class_t * const cls) {
    ctb_DList_forEach(&cls->inboxes, onTick);
}

vsk_Inbox_t * vsk_Inbox_init(vsk_Inbox_t * const self, vsk_Task_t * const task) {
    self->cls  = &vsk_Inbox_Class;
    self->task = task;
    ctb_Queue_init(&self->messageQueue);
    registerInbox(&vsk_Inbox_Class, self);
    return self;
}

bool vsk_Inbox_isEmpty(vsk_Inbox_t * const self) {
    bool isEmpty;
    vsk_CriticalSection_enter(&vsk_CriticalSection);
    isEmpty = ctb_Queue_isEmpty(&self->messageQueue);
    vsk_CriticalSection_exit(&vsk_CriticalSection);
    return isEmpty;
}

void vsk_Inbox_postMessage(
    vsk_Inbox_t * const self, vsk_Message_t * const message
) {
    vsk_CriticalSection_enter(&vsk_CriticalSection);
    ctb_Queue_enqueue(&self->messageQueue, (ctb_DNode_t *)message);
    vsk_Task_activate(self->task);
    vsk_CriticalSection_exit(&vsk_CriticalSection);
}

vsk_Message_t * vsk_Inbox_readMessage(vsk_Inbox_t * const self) {
    vsk_CriticalSection_enter(&vsk_CriticalSection);
    ctb_DNode_t * const messageNode = ctb_Queue_dequeue(&self->messageQueue);
    vsk_CriticalSection_exit(&vsk_CriticalSection);
    vsk_Message_t * const message = ctb_containerOf(
        messageNode, vsk_Message_t, node
    );
    return message;
}

// cppcheck-suppress unusedFunction // API function
void vsk_Inbox_clear(vsk_Inbox_t * const self) {
    vsk_CriticalSection_enter(&vsk_CriticalSection);
    ctb_Queue_clear(&self->messageQueue);
    vsk_CriticalSection_exit(&vsk_CriticalSection);
}

void vsk_Inbox_onTick(vsk_Inbox_t * const self) {
    if (!vsk_Inbox_isEmpty(self)) {
        vsk_Task_activate(self->task);
    }
}
