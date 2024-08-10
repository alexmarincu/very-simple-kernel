/*----------------------------------------------------------------------------*/
#ifndef VSK_H
#define VSK_H
/*----------------------------------------------------------------------------*/
#include "vsk_Assert.h"
#include "vsk_CriticalSection.h"
#include "vsk_TaskScheduler.h"
/*----------------------------------------------------------------------------*/
void vsk_start(
    uint16_t const tickPeriodMillis,
    vsk_TaskSchedulerOnStart const onStart,
    vsk_TaskSchedulerOnIdle const onIdle,
    vsk_CriticalSectionOnEnter const onCriticalSectionEnter,
    vsk_CriticalSectionOnExit const onCriticalSectionExit,
    vsk_AssertOnFail const onAssertFail
);
void vsk_onTick(void);
#endif // VSK_H
