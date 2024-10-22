/**
 * @file
 */
#ifndef VSK_CRITICALSECTION_H
#define VSK_CRITICALSECTION_H
/**
 * @ingroup vsk
 * @defgroup vsk_CriticalSection vsk_CriticalSection
 * @{
 */

/**
 * @brief Critical section
 */
typedef struct vsk_CriticalSection vsk_CriticalSection_t;

#include <stdint.h>

/**
 * @brief On enter callback
 */
typedef void (*vsk_CriticalSection_OnEnter_t)(void);

/**
 * @brief On exit callback
 */
typedef void (*vsk_CriticalSection_OnExit_t)(void);

/**
 * @brief Critical section
 */
struct vsk_CriticalSection {
    vsk_CriticalSection_OnEnter_t onEnter; /**< Called on entering a critical section */
    vsk_CriticalSection_OnExit_t  onExit;  /**< Called on exiting a critical section */
    uint8_t volatile nestingLevels;        /**< The nesting level of the critical section */
};

/**
 * @brief Critical section instance
 */
extern vsk_CriticalSection_t vsk_CriticalSection;

/**
 * @brief Initializes the critical section.
 *
 * @param self Critical section reference
 * @param onEnter On enter callback
 * @param onExit On exit callback
 * @return Initialized critical section
 */
vsk_CriticalSection_t * vsk_CriticalSection_init(
    vsk_CriticalSection_t * const       self,
    vsk_CriticalSection_OnEnter_t const onEnter,
    vsk_CriticalSection_OnExit_t const  onExit
);

/**
 * @brief Enters a critical section
 *
 * @param self Critical section reference
 */
void vsk_CriticalSection_enter(vsk_CriticalSection_t * const self);

/**
 * @brief Exits a critical section
 *
 * @param self Critical section reference
 */
void vsk_CriticalSection_exit(vsk_CriticalSection_t * const self);

/** @} */
#endif // VSK_CRITICALSECTION_H
