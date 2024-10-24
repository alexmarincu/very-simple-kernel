/**
 * @file
 */
#ifndef VSK_STATECONTEXT_H
#define VSK_STATECONTEXT_H
/**
 * @ingroup vsk
 * @defgroup vsk_StateContext vsk_StateContext
 * @{
 */

/**
 * @brief State context
 */
typedef struct vsk_StateContext vsk_StateContext_t;

#include "vsk_State.h"

/**
 *  @brief State context
 */
struct vsk_StateContext {
    vsk_State_t * state;        /**< Current state */
    vsk_State_t * initialState; /**< Initial state */
};

/**
 * @brief Initializes a state context
 *
 * @param self State context reference
 * @param initialState Initial state
 * @return Initialized state context reference
 */
vsk_StateContext_t * vsk_StateContext_init(
    vsk_StateContext_t * const self, vsk_State_t * const initialState
);

/**
 * @brief Transitions the context to a new state
 *
 * @param self State context reference
 * @param state New state to transition to
 */
void vsk_StateContext_transition(
    vsk_StateContext_t * const self, vsk_State_t * const state
);

/** @} */
#endif // VSK_STATECONTEXT_H
