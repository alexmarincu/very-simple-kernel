/**
 * @file
 */
#ifndef VSK_ONSTARTEVENT_H
#define VSK_ONSTARTEVENT_H
/**
 * @ingroup vsk
 * @defgroup vsk_OnStartEvent vsk_OnStartEvent
 * @{
 */

/**
 * @brief On start event
 */
typedef struct vsk_OnStartEvent vsk_OnStartEvent_t;

#include "vsk_Event.h"

/**
 * @brief On start event
 */
struct vsk_OnStartEvent {
    vsk_Event_t event; /**< Event with subscriptions */
};

/**
 * @brief On start event instance
 */
extern vsk_OnStartEvent_t vsk_OnStartEvent;

/**
 * @brief Initializes the on start event
 *
 * @param self On start event reference
 * @return Initialized on start event reference
 */
vsk_OnStartEvent_t * vsk_OnStartEvent_init(vsk_OnStartEvent_t * const self);

/** @} */
#endif // VSK_ONSTARTEVENT_H
