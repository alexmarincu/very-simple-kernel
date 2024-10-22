/**
 * @file
 */
#ifndef VSK_EVENTTIMER_H
#define VSK_EVENTTIMER_H
/**
 * @ingroup vsk
 * @defgroup vsk_EventTimer vsk_EventTimer
 * @{
 */

/**
 * @brief Event timer
 */
typedef struct vsk_EventTimer vsk_EventTimer_t;

#include "vsk_Event.h"
#include "vsk_Timer.h"

/**
 * @brief Event timer
 */
struct vsk_EventTimer {
    vsk_Timer_t   timer; /**< Timer */
    vsk_Event_t * event; /**< Associated Event reference */
};

/**
 * @brief Initializes an event timer
 *
 * @param self Event timer reference
 * @param delayMillis Initial delay of the timer in milliseconds
 * @param periodMillis Period of the timer after the initial delay in milliseconds
 * @param event Associated event reference
 * @return Initialized event timer reference
 */
vsk_EventTimer_t * vsk_EventTimer_init(
    vsk_EventTimer_t * const self,
    uint32_t const           delayMillis,
    uint32_t const           periodMillis,
    vsk_Event_t * const      event
);

/** @} */
#endif // VSK_EVENTTIMER_H
