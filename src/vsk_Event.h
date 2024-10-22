/**
 * @file
 */
#ifndef VSK_EVENT_H
#define VSK_EVENT_H
/**
 * @ingroup vsk
 * @defgroup vsk_Event vsk_Event
 * @{
 */

/**
 * @brief Event
 */
typedef struct vsk_Event vsk_Event_t;

#include "ctb_DList.h"
#include "vsk_EventSubscription.h"

/**
 * @brief Event
 */
struct vsk_Event {
    ctb_DList_t eventSubscriptions; /**< Event subscriptions */
};

/**
 * @brief Initializes an event
 *
 * @param self Event reference
 * @return Initialized Event reference
 */
vsk_Event_t * vsk_Event_init(vsk_Event_t * const self);

/**
 * @brief Raises an event
 *
 * @param self Event reference
 */
void vsk_Event_raise(vsk_Event_t * const self);

/**
 * @brief Subscribes to an event
 *
 * @param self Event reference
 * @param subscription Event subscription reference
 */
void vsk_Event_subscribe(
    vsk_Event_t * const self, vsk_EventSubscription_t * const subscription
);

/** @} */
#endif // VSK_EVENT_H
