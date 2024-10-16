/**
 * @file
 */
#ifndef VSK_TIMER_H
#define VSK_TIMER_H

typedef struct vsk_Timer_Class vsk_Timer_Class_t;
typedef struct vsk_Timer       vsk_Timer_t;
typedef void (*vsk_Timer_Callback_t)(void * const obj);

#include "ctb_DList.h"
#include "ctb_DNode.h"
#include <stdbool.h>
#include <stdint.h>

struct vsk_Timer_Class {
    ctb_DList_t timers;
};

struct vsk_Timer {
    vsk_Timer_Class_t *  cls;
    ctb_DNode_t          node;
    uint32_t             delayMillis;
    uint32_t             periodMillis;
    vsk_Timer_Callback_t callback;
    void *               obj;
    uint32_t volatile millisCountDown;
    bool volatile isRunning;
};

extern vsk_Timer_Class_t vsk_Timer_Class;

vsk_Timer_Class_t * vsk_Timer_Class_init(
    vsk_Timer_Class_t * const cls
);

void vsk_Timer_Class_onTick(vsk_Timer_Class_t * const cls);

vsk_Timer_t * vsk_Timer_init(
    vsk_Timer_t * const        self,
    uint32_t const             delayMillis,
    uint32_t const             periodMillis,
    vsk_Timer_Callback_t const callback,
    void * const               obj
);

void vsk_Timer_start(vsk_Timer_t * const self);

void vsk_Timer_stop(vsk_Timer_t * const self);

bool vsk_Timer_isRunning(vsk_Timer_t * const self);

void vsk_Timer_onTick(vsk_Timer_t * const self);

#endif // VSK_TIMER_H
