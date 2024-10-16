#include "vsk.h"
#include "vsk_Inbox.h"
#include "vsk_OnStartEvent.h"
#include "vsk_Time.h"
#include "vsk_Timer.h"

// cppcheck-suppress unusedFunction // API function
void vsk_init(
    uint16_t const        tickPeriodMillis,
    vsk_Interface_t const interface
) {
    vsk_Time_init(&vsk_Time, tickPeriodMillis);
    vsk_Task_Class_init(
        &vsk_Task_Class, interface.onStart, interface.onIdle
    );
    vsk_Timer_Class_init(&vsk_Timer_Class);
    vsk_Inbox_Class_init(&vsk_Inbox_Class);
    vsk_CriticalSection_init(
        &vsk_CriticalSection,
        interface.onCriticalSectionEnter,
        interface.onCriticalSectionExit
    );
    vsk_Assert_init(&vsk_Assert, interface.onAssertFail);
    vsk_OnStartEvent_init(&vsk_OnStartEvent);
}

// cppcheck-suppress unusedFunction // API function
void vsk_onTick(void) {
    vsk_Time_onTick(&vsk_Time);
    vsk_Timer_Class_onTick(&vsk_Timer_Class);
    vsk_Inbox_Class_onTick(&vsk_Inbox_Class);
}

// cppcheck-suppress unusedFunction // API function
void vsk_startScheduler(void) {
    vsk_Task_Class_startScheduler(&vsk_Task_Class);
}
