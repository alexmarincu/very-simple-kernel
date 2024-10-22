/**
 * @file
 */
#ifndef VSK_EVENTSUBSCRIPTION_H
#define VSK_EVENTSUBSCRIPTION_H
/**
 * @ingroup vsk
 * @defgroup vsk_EventSubscription vsk_EventSubscription
 * @{
 */

/**
 * @brief Event subscription
 */
typedef struct vsk_EventSubscription vsk_EventSubscription_t;

#include "vsk_Inbox.h"
#include "vsk_Message.h"

/**
 * @brief Event subscription
 */
struct vsk_EventSubscription {
    ctb_DNode_t   node;    /**< Node to allow event subscription to be added to a list */
    vsk_Inbox_t * inbox;   /**< Inbox to post the event message to */
    vsk_Message_t message; /**< Message to post to the inbox */
};

/**
 * @brief Initializes an event subscription
 *
 * @param self Event subscription reference
 * @param inbox Inbox to post the event message to
 * @param handler Message handler to be called when the event is dispatched
 * @param obj Object reference to pass to the handler
 * @return Initialized event subscription
 */
vsk_EventSubscription_t * vsk_EventSubscription_init(
    vsk_EventSubscription_t * const self,
    vsk_Inbox_t * const             inbox,
    vsk_Message_Handler_t const     handler,
    void * const                    obj
);

/**
 * @brief Publishes the event message to the associated inbox
 *
 * @param self Event subscription reference
 */
void vsk_EventSubscription_publish(vsk_EventSubscription_t * const self);

/** @} */
#endif // VSK_EVENTSUBSCRIPTION_H
