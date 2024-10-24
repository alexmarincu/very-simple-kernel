/**
 * @file
 */
#ifndef VSK_TIMER_H
#define VSK_TIMER_H
/**
 * @ingroup vsk
 * @defgroup vsk_Timer vsk_Timer
 * @{
 */

/**
 * @brief Timer class
 */
typedef struct vsk_Timer_Class vsk_Timer_Class_t;

/**
 * @brief Software timer
 */
typedef struct vsk_Timer vsk_Timer_t;

/**
 * @brief Timer callback
 */
typedef void (*vsk_Timer_Callback_t)(void * const obj);

#include "ctb_DList.h"
#include "ctb_DNode.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Timer class
 */
struct vsk_Timer_Class {
    ctb_DList_t timers; /**< List of registered timers */
};

/**
 * @brief Software timer
 */
struct vsk_Timer {
    vsk_Timer_Class_t *  cls;          /**< Timer class reference */
    ctb_DNode_t          node;         /**< Node to allow timer to be added to a list */
    uint32_t             delayMillis;  /**< Initial delay of the timer in milliseconds */
    uint32_t             periodMillis; /**< Period of the timer after the initial delay in milliseconds */
    vsk_Timer_Callback_t callback;     /**< Callback function (called on timer expiration) */
    void *               obj;          /**< Object reference to pass to the callback (can be NULL) */
    uint32_t volatile millisCountDown; /**< Milliseconds until the timer expires */
    bool volatile isRunning;           /**< Timer running state */
};

/**
 * @brief Timer class instance
 */
extern vsk_Timer_Class_t vsk_Timer_Class;

/**
 * @brief Initializes the Timer class
 *
 * @param cls Timer class reference
 * @return Initialized Timer class reference
 */
vsk_Timer_Class_t * vsk_Timer_Class_init(vsk_Timer_Class_t * const cls);

/**
 * @brief Propagates the system tick to all timers
 *
 * @param cls Timer class reference
 */
void vsk_Timer_Class_onTick(vsk_Timer_Class_t * const cls);

/**
 * @brief Initializes a timer
 *
 * @param self Timer reference
 * @param delayMillis Initial delay of the timer in milliseconds
 * @param periodMillis Period of the timer after the initial delay in milliseconds
 * @param callback Callback function (called on timer expiration)
 * @param obj Object reference to pass to the callback (can be NULL)
 * @return Initialized Timer reference
 */
vsk_Timer_t * vsk_Timer_init(
    vsk_Timer_t * const        self,
    uint32_t const             delayMillis,
    uint32_t const             periodMillis,
    vsk_Timer_Callback_t const callback,
    void * const               obj
);

/**
 * @brief Starts the timer
 *
 * @param self Timer reference
 */
void vsk_Timer_start(vsk_Timer_t * const self);

/**
 * @brief Stops the timer
 *
 * @param self Timer reference
 */
void vsk_Timer_stop(vsk_Timer_t * const self);

/**
 * @brief Checks if the timer is running
 *
 * @param self Timer reference
 * @return true if the timer is running
 * @return false if the timer is not running
 */
bool vsk_Timer_isRunning(vsk_Timer_t * const self);

/** @} */
#endif // VSK_TIMER_H
