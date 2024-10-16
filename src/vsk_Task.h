/**
 * @file
 */
#ifndef VSK_TASK_H
#define VSK_TASK_H

typedef struct vsk_Task_Class vsk_Task_Class_t;
typedef void (*vsk_Task_Class_OnStart_t)(void);
typedef void (*vsk_Task_Class_OnIdle_t)(void);
typedef struct vsk_Task vsk_Task_t;
typedef void (*vsk_Task_Operation_t)(void * const obj);

#include "ctb_DList.h"
#include "vsk_Task.h"
#include <stdbool.h>
#include <stdint.h>

struct vsk_Task_Class {
    ctb_DList_t              tasks;
    vsk_Task_Class_OnStart_t onStart;
    vsk_Task_Class_OnIdle_t  onIdle;
};

typedef enum {
    vsk_Task_State_suspended,
    vsk_Task_State_ready,
    vsk_Task_State_running
} vsk_Task_State_t;

struct vsk_Task {
    vsk_Task_Class_t *   cls;
    ctb_DNode_t          node;
    vsk_Task_Operation_t operation;
    void *               obj;
    vsk_Task_State_t     state;
    uint32_t             lastStartTimeMillis;
    uint32_t             maxRunTimeMillis;
    uint32_t             minPeriodMillis;
    uint32_t             cpuLoad;
};

extern vsk_Task_Class_t vsk_Task_Class;

vsk_Task_Class_t * vsk_Task_Class_init(
    vsk_Task_Class_t * const       cls,
    vsk_Task_Class_OnStart_t const onStart,
    vsk_Task_Class_OnIdle_t const  onIdle
);

void vsk_Task_Class_startScheduler(vsk_Task_Class_t * const cls);

vsk_Task_t * vsk_Task_init(
    vsk_Task_t * const self, vsk_Task_Operation_t const operation, void * const obj
);

bool vsk_Task_isReady(vsk_Task_t * const self);

void vsk_Task_activate(vsk_Task_t * const self);

void vsk_Task_suspend(vsk_Task_t * const self);

ctb_DNode_t * vsk_Task_toNode(vsk_Task_t * const self);

#endif // VSK_TASK_H
