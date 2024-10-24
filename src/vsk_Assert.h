/**
 * @file
 */
#ifndef VSK_ASSERT_H
#define VSK_ASSERT_H
/**
 * @ingroup vsk
 * @defgroup vsk_Assert vsk_Assert
 * @{
 */

/**
 * @brief Assert
 */
typedef struct vsk_Assert vsk_Assert_t;

#include <stdbool.h>

/**
 * @brief On fail callback
 */
typedef void (*vsk_Assert_OnFail_t)(void);

/**
 * @brief Assert
 */
struct vsk_Assert {
    vsk_Assert_OnFail_t onFail; /**< On fail callback */
};

/**
 * @brief Assert instance
 */
extern vsk_Assert_t vsk_Assert;

/**
 * @brief Initializes the assert instance
 *
 * @param self Assert instance
 * @param onFail On fail callback
 * @return InitializedAssert instance
 */
vsk_Assert_t * vsk_Assert_init(
    vsk_Assert_t * const self, vsk_Assert_OnFail_t const onFail
);

/**
 * @brief Asserts that a condition is true
 *
 * @param self Assert instance
 * @param condition Condition to assert
 */
void vsk_Assert_true(vsk_Assert_t * const self, bool const condition);

/**
 * @brief Fails the assert
 *
 * @param self Assert instance
 */
void vsk_Assert_fail(vsk_Assert_t * const self);

/** @} */
#endif // VSK_ASSERT_H
