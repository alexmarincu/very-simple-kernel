#include "vsk_ActiveObject.h"
#include "vsk_OnStartEvent.h"

static void onStart(vsk_ActiveObject_t * const self);

static void dispatchMessage(vsk_ActiveObject_t * const self) {
    vsk_Message_dispatch(vsk_Inbox_readMessage(&self->inbox));
}

// cppcheck-suppress unusedFunction // API function
vsk_ActiveObject_t * vsk_ActiveObject_init(
    vsk_ActiveObject_t * const self, vsk_State_t * const initialState
) {
    vsk_StateContext_init((vsk_StateContext_t *)self, initialState);
    vsk_Task_init(&self->task, (vsk_Task_Operation_t)dispatchMessage, self);
    vsk_Inbox_init(&self->inbox, &self->task);
    vsk_Event_subscribe(
        (vsk_Event_t *)&vsk_OnStartEvent,
        vsk_EventSubscription_init(
            &self->eventSubscriptions.onStart,
            &self->inbox,
            (vsk_Message_Handler_t)onStart,
            self
        )
    );
    return self;
}

static void onStart(vsk_ActiveObject_t * const self) {
    vsk_StateContext_transition(
        (vsk_StateContext_t *)self, ((vsk_StateContext_t *)self)->initialState
    );
}
