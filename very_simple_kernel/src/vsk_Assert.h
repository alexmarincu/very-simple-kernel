/*----------------------------------------------------------------------------*/
#ifndef VSK_ASSERT_H
#define VSK_ASSERT_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_Assert vsk_Assert;
/*----------------------------------------------------------------------------*/
#include <stdbool.h>
/*----------------------------------------------------------------------------*/
typedef void (*vsk_AssertOnFail)(void);
/*----------------------------------------------------------------------------*/
struct vsk_Assert {
    vsk_AssertOnFail _onFail;
};
/*----------------------------------------------------------------------------*/
vsk_Assert * vsk_Assert_(void);
vsk_Assert * vsk_Assert_init(
    vsk_Assert * const self, vsk_AssertOnFail const onFail
);
void vsk_Assert_true(vsk_Assert * const self, bool const condition);
void vsk_Assert_fail(vsk_Assert * const self);
#endif // VSK_ASSERT_H
