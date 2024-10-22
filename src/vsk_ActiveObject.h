/**
 * @file
 */
#ifndef VSK_ACTIVEOBJECT_H
#define VSK_ACTIVEOBJECT_H
/**
 * @ingroup vsk
 * @defgroup vsk_ActiveObject vsk_ActiveObject
 * @{
 */

/**
 * @brief Active object
 */
typedef struct vsk_ActiveObject vsk_ActiveObject_t;

#include "vsk_EventSubscription.h"
#include "vsk_StateContext.h"
#include "vsk_Task.h"

/**
 * @brief Active object
 */
struct vsk_ActiveObject {
    vsk_StateContext_t stateContext; /**< State context */
    vsk_Task_t         task;         /**< Task that runs the active object */
    vsk_Inbox_t        inbox;        /**< Inbox in which messages are posted to the active object */
    struct {
        vsk_EventSubscription_t onStart; /**< Event subscription for the on start event */
    } eventSubscriptions;
};

/**
 * @brief Initializes an active object
 *
 * @param self Active object reference
 * @param initialState Initial state
 *
 * @return Initialized Active object reference
 */
vsk_ActiveObject_t * vsk_ActiveObject_init(
    vsk_ActiveObject_t * const self, vsk_State_t * const initialState
);

/** @} */
#endif // VSK_ACTIVEOBJECT_H
