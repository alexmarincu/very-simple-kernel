/**
 * @file
 */
#ifndef VSK_STATE_H
#define VSK_STATE_H
/**
 * @ingroup vsk
 * @defgroup vsk_State vsk_State
 * @{
 */

/**
 * @brief State
 */
typedef struct vsk_State vsk_State_t;

#include "vsk_StateContext.h"
#include <stdbool.h>

/**
 * @brief On enter callback
 */
typedef void (*vsk_State_OnEnter_t)(vsk_State_t * const self);

/**
 * @brief On exit callback
 */
typedef void (*vsk_State_OnExit_t)(vsk_State_t * const self);

/**
 * @brief State
 */
struct vsk_State {
    vsk_StateContext_t * stateContext; /**< State context */
    vsk_State_OnEnter_t  onEnter;      /**< On enter callback */
    vsk_State_OnExit_t   onExit;       /**< On exit callback */
};

/**
 * @brief Initializes a state
 *
 * @param self State reference
 * @param stateContext Corresponding state context
 * @return Initialized state reference
 */
vsk_State_t * vsk_State_init(
    vsk_State_t * const self, vsk_StateContext_t * const stateContext
);

/**
 * @brief Executes entry logic
 *
 * @param self State reference
 */
void vsk_State_onEnter(vsk_State_t * const self);

/**
 * @brief Executes exit logic
 *
 * @param self State reference
 */
void vsk_State_onExit(vsk_State_t * const self);

/** @} */
#endif // VSK_STATE_H
