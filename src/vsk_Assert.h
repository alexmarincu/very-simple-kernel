/**
 * @file
 */
#ifndef VSK_ASSERT_H
#define VSK_ASSERT_H

typedef struct vsk_Assert vsk_Assert_t;

#include <stdbool.h>

typedef void (*vsk_Assert_OnFail_t)(void);

struct vsk_Assert {
    vsk_Assert_OnFail_t onFail;
};

extern vsk_Assert_t vsk_Assert;

vsk_Assert_t * vsk_Assert_init(
    vsk_Assert_t * const self, vsk_Assert_OnFail_t const onFail
);

void vsk_Assert_true(vsk_Assert_t * const self, bool const condition);

void vsk_Assert_fail(vsk_Assert_t * const self);

#endif // VSK_ASSERT_H
