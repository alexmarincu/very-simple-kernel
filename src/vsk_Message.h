/**
 * @file
 */
#ifndef VSK_MESSAGE_H
#define VSK_MESSAGE_H
/**
 * @ingroup vsk
 * @defgroup vsk_Message vsk_Message
 * @{
 */

/**
 * @brief Message
 */
typedef struct vsk_Message vsk_Message_t;

#include "ctb_DNode.h"

/**
 * @brief Message handler
 */
typedef void (*vsk_Message_Handler_t)(void * const obj);

/**
 * @brief Message
 */
struct vsk_Message {
    ctb_DNode_t           node;    /**< Node to allow message to be enqueued */
    vsk_Message_Handler_t handler; /**< Handler to be called when message is dispatched */
    void *                obj;     /**< Object to be passed to the handler */
};

/**
 * @brief Initializes a message
 *
 * @param self Message reference
 * @param handler Message handler
 * @param obj Object reference to pass to the handler
 * @return Initialized message reference
 */
vsk_Message_t * vsk_Message_init(
    vsk_Message_t * const       self,
    vsk_Message_Handler_t const handler,
    void * const                obj
);

/**
 * @brief Dispatches a message
 *
 * @param self Message reference
 */
void vsk_Message_dispatch(vsk_Message_t * const self);

/** @} */
#endif // VSK_MESSAGE_H
