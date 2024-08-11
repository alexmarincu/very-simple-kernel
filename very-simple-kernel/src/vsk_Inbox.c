/*----------------------------------------------------------------------------*/
#include "vsk_Inbox.h"
/*----------------------------------------------------------------------------*/
#include "../../c-tool-box/c_tool_box/src/ctb.h"
#include "vsk_CriticalSection.h"
#include "vsk_InboxSupervisor.h"
/*----------------------------------------------------------------------------*/
vsk_Inbox * vsk_Inbox_init(vsk_Inbox * const self, vsk_Task * const task) {
    self->task = task;
    ctb_LinkedQueue_init(&self->messageQueue);
    vsk_InboxSupervisor_register(vsk_InboxSupervisor_(), self);
    return self;
}
/*----------------------------------------------------------------------------*/
bool vsk_Inbox_isEmpty(vsk_Inbox * const self) {
    bool isEmpty;
    vsk_CriticalSection_enter(vsk_CriticalSection_());
    isEmpty = ctb_LinkedQueue_isEmpty(&self->messageQueue);
    vsk_CriticalSection_exit(vsk_CriticalSection_());
    return isEmpty;
}
/*----------------------------------------------------------------------------*/
void vsk_Inbox_postMessage(
    vsk_Inbox * const self, vsk_Message * const message
) {
    vsk_CriticalSection_enter(vsk_CriticalSection_());
    ctb_LinkedQueue_enqueue(&self->messageQueue, (ctb_Node *)message);
    vsk_Task_activate(self->task);
    vsk_CriticalSection_exit(vsk_CriticalSection_());
}
/*----------------------------------------------------------------------------*/
vsk_Message * vsk_Inbox_readMessage(vsk_Inbox * const self) {
    vsk_Message * message;
    vsk_CriticalSection_enter(vsk_CriticalSection_());
    message = ctb_containerOf(
        ctb_LinkedQueue_dequeue(&self->messageQueue), vsk_Message, node
    );
    vsk_CriticalSection_exit(vsk_CriticalSection_());
    return message;
}
/*----------------------------------------------------------------------------*/
// cppcheck-suppress unusedFunction // API function
void vsk_Inbox_clear(vsk_Inbox * const self) {
    vsk_CriticalSection_enter(vsk_CriticalSection_());
    ctb_LinkedQueue_clear(&self->messageQueue);
    vsk_CriticalSection_exit(vsk_CriticalSection_());
}
/*----------------------------------------------------------------------------*/
void vsk_Inbox_onTick(vsk_Inbox * const self) {
    if (!vsk_Inbox_isEmpty(self)) {
        vsk_Task_activate(self->task);
    }
}
