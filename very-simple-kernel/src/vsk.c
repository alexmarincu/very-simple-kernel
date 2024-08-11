/*----------------------------------------------------------------------------*/
#include "vsk.h"
/*----------------------------------------------------------------------------*/
#include "vsk_InboxSupervisor.h"
#include "vsk_OnStartEvent.h"
#include "vsk_Time.h"
#include "vsk_TimerSupervisor.h"
/*----------------------------------------------------------------------------*/
// cppcheck-suppress unusedFunction // API function
void vsk_start(
    uint16_t const tickPeriodMillis,
    vsk_TaskSchedulerOnStart const onStart,
    vsk_TaskSchedulerOnIdle const onIdle,
    vsk_CriticalSectionOnEnter const onCriticalSectionEnter,
    vsk_CriticalSectionOnExit const onCriticalSectionExit,
    vsk_AssertOnFail const onAssertFail
) {
    vsk_Time_init(vsk_Time_(), tickPeriodMillis);
    vsk_TaskScheduler_init(vsk_TaskScheduler_(), onStart, onIdle);
    vsk_TimerSupervisor_init(vsk_TimerSupervisor_());
    vsk_InboxSupervisor_init(vsk_InboxSupervisor_());
    vsk_CriticalSection_init(
        vsk_CriticalSection_(), onCriticalSectionEnter, onCriticalSectionExit
    );
    vsk_Assert_init(vsk_Assert_(), onAssertFail);
    vsk_OnStartEvent_init(vsk_OnStartEvent_());
    vsk_TaskScheduler_start(vsk_TaskScheduler_());
}
/*----------------------------------------------------------------------------*/
void vsk_onTick(void) {
    vsk_Time_onTick(vsk_Time_());
    vsk_TimerSupervisor_onTick(vsk_TimerSupervisor_());
    vsk_InboxSupervisor_onTick(vsk_InboxSupervisor_());
}
