/**
 * @file
 */
#ifndef VSK_INBOX_H
#define VSK_INBOX_H
/**
 * @ingroup vsk
 * @defgroup vsk_Inbox vsk_Inbox
 * @{
 */

/**
 * @brief Inbox class
 */
typedef struct vsk_Inbox_Class vsk_Inbox_Class_t;

/**
 * @brief Inbox
 */
typedef struct vsk_Inbox vsk_Inbox_t;

#include "ctb_Queue.h"
#include "vsk_Message.h"
#include "vsk_Task.h"

/**
 * @brief Inbox class
 */
struct vsk_Inbox_Class {
    ctb_DList_t inboxes;
};

/**
 * @brief Inbox
 */
struct vsk_Inbox {
    vsk_Inbox_Class_t * cls;          /**< Inbox class reference */
    ctb_DNode_t         node;         /**< Node to allow inbox to be added to a list */
    vsk_Task_t *        task;         /**< Associated Task reference */
    ctb_Queue_t         messageQueue; /**< Queue of messages */
};

/**
 * @brief Inbox class instance
 */
extern vsk_Inbox_Class_t vsk_Inbox_Class;

/**
 * @brief Initializes the Inbox class
 *
 * @param cls Inbox class reference
 * @return Initialized Inbox class reference
 */
vsk_Inbox_Class_t * vsk_Inbox_Class_init(vsk_Inbox_Class_t * const cls);

/**
 * @brief Propagates the system tick to all inboxes
 *
 * @param cls Inbox class reference
 */
void vsk_Inbox_Class_onTick(vsk_Inbox_Class_t * const cls);

/**
 * @brief Initializes an Inbox
 *
 * @param self Inbox reference
 * @param task Associated Task reference
 * @return Initialized Inbox reference
 */
vsk_Inbox_t * vsk_Inbox_init(vsk_Inbox_t * const self, vsk_Task_t * const task);

/**
 * @brief Checks if the inbox is empty
 *
 * @param self Inbox reference
 * @return true if the inbox is empty
 * @return false if the inbox is not empty
 */
bool vsk_Inbox_isEmpty(vsk_Inbox_t * const self);

/**
 * @brief Posts a message to the inbox
 *
 * @param self Inbox reference
 * @param message Message reference
 */
void vsk_Inbox_postMessage(vsk_Inbox_t * const self, vsk_Message_t * const message);

/**
 * @brief Reads a message from the inbox
 *
 * @param self Inbox reference
 * @return Message reference
 */
vsk_Message_t * vsk_Inbox_readMessage(vsk_Inbox_t * const self);

/**
 * @brief Clears the inbox
 *
 * @param self Inbox reference
 */
void vsk_Inbox_clear(vsk_Inbox_t * const self);

/** @} */
#endif // VSK_INBOX_H
