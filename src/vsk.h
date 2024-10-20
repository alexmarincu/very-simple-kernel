/**
 * @file
 */
#ifndef VSK_H
#define VSK_H

#include "vsk_Assert.h"
#include "vsk_CriticalSection.h"
#include "vsk_Task.h"

/**
 * @brief Data type and structure for vsk interfaces
 */
typedef struct vsk_Interface {
    vsk_Task_Class_OnStart_t      onStart;                /**< Called on task scheduler start. */
    vsk_Task_Class_OnIdle_t       onIdle;                 /**< Called when the system is idle. */
    vsk_Assert_OnFail_t           onAssertFail;           /**< Called when an assertion fails. */
    vsk_CriticalSection_OnEnter_t onCriticalSectionEnter; /**< Called on entering a critical section. */
    vsk_CriticalSection_OnExit_t  onCriticalSectionExit;  /**< Called on exiting a critical section. */
} vsk_Interface_t;

/**
 * @brief Initializes the vsk module.
 *
 * @param tickPeriodMillis The period at which the system ticks
 * @param interface        The interface for user hooks and platform specific functions
 */
void vsk_init(
    uint16_t const                tickPeriodMillis,
    vsk_Interface_t const * const interface
);

/**
 * @brief Propagates the system tick in the vsk module
 *
 * @remark Must be called from the system tick
 */
void vsk_onTick(void);

/**
 * @brief Starts the task scheduler
 *
 */
void vsk_startScheduler(void);

#endif // VSK_H
