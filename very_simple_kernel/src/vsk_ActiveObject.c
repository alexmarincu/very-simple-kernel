/*----------------------------------------------------------------------------*/
#include "vsk_ActiveObject.h"
/*----------------------------------------------------------------------------*/
#include "vsk_OnStartEvent.h"
/*----------------------------------------------------------------------------*/
static void vsk_ActiveObject_onStart(vsk_ActiveObject * const self);
/*----------------------------------------------------------------------------*/
static void vsk_dispatchMessage(vsk_ActiveObject * const self) {
    vsk_Message_dispatch(vsk_Inbox_readMessage(&self->_inbox));
}
/*----------------------------------------------------------------------------*/
vsk_ActiveObject * vsk_ActiveObject_init(
    vsk_ActiveObject * const self, vsk_State * const initialState
) {
    vsk_StateContext_init((vsk_StateContext *)self, initialState);
    vsk_Task_init(&self->_task, (vsk_TaskOperation)vsk_dispatchMessage, self);
    vsk_Inbox_init(&self->_inbox, &self->_task);
    vsk_Event_subscribe(
        (vsk_Event *)vsk_OnStartEvent_(),
        vsk_EventSubscription_init(
            &self->_eventSubscriptions.onStart,
            &self->_inbox,
            (vsk_MessageHandler)vsk_ActiveObject_onStart,
            self
        )
    );
    return self;
}
/*----------------------------------------------------------------------------*/
static void vsk_ActiveObject_onStart(vsk_ActiveObject * const self) {
    vsk_StateContext_transition(
        (vsk_StateContext *)self, ((vsk_StateContext *)self)->_initialState
    );
}
