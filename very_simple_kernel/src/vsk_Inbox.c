/*----------------------------------------------------------------------------*/
#include "vsk_Inbox.h"
/*----------------------------------------------------------------------------*/
#include "../../c_tool_box/c_tool_box/src/ctb.h"
#include "vsk_CriticalSection.h"
#include "vsk_InboxSupervisor.h"
/*----------------------------------------------------------------------------*/
vsk_Inbox * vsk_Inbox_init(vsk_Inbox * const self, vsk_Task * const task) {
    self->_task = task;
    ctb_LinkedQueue_init(&self->_messageQueue);
    vsk_InboxSupervisor_register(vsk_InboxSupervisor_(), self);
    return self;
}
/*----------------------------------------------------------------------------*/
bool vsk_Inbox_isEmpty(vsk_Inbox * const self) {
    bool isEmpty;
    vsk_CriticalSection_enter(vsk_CriticalSection_());
    isEmpty = ctb_LinkedQueue_isEmpty(&self->_messageQueue);
    vsk_CriticalSection_exit(vsk_CriticalSection_());
    return isEmpty;
}
/*----------------------------------------------------------------------------*/
void vsk_Inbox_postMessage(
    vsk_Inbox * const self, vsk_Message * const message
) {
    vsk_CriticalSection_enter(vsk_CriticalSection_());
    ctb_LinkedQueue_enqueue(&self->_messageQueue, (ctb_Node *)message);
    vsk_Task_activate(self->_task);
    vsk_CriticalSection_exit(vsk_CriticalSection_());
}
/*----------------------------------------------------------------------------*/
vsk_Message * vsk_Inbox_readMessage(vsk_Inbox * const self) {
    vsk_Message * message;
    vsk_CriticalSection_enter(vsk_CriticalSection_());
    message = ctb_containerOf(ctb_LinkedQueue_dequeue(&self->_messageQueue), vsk_Message, _super.node);
    vsk_CriticalSection_exit(vsk_CriticalSection_());
    return message;
}
/*----------------------------------------------------------------------------*/
void vsk_Inbox_clear(vsk_Inbox * const self) {
    vsk_CriticalSection_enter(vsk_CriticalSection_());
    ctb_LinkedQueue_clear(&self->_messageQueue);
    vsk_CriticalSection_exit(vsk_CriticalSection_());
}
/*----------------------------------------------------------------------------*/
void vsk_Inbox_onSysTick(vsk_Inbox * const self) {
    if (!vsk_Inbox_isEmpty(self)) {
        vsk_Task_activate(self->_task);
    }
}
