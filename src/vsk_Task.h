/**
 * @file
 */
#ifndef VSK_TASK_H
#define VSK_TASK_H
/**
 * @ingroup vsk
 * @defgroup vsk_Task vsk_Task
 * @{
 */

/**
 * @brief Task class
 */
typedef struct vsk_Task_Class vsk_Task_Class_t;

/**
 * @brief On start callback
 */
typedef void (*vsk_Task_Class_OnStart_t)(void);

/**
 * @brief On idle callback
 */
typedef void (*vsk_Task_Class_OnIdle_t)(void);

/**
 * @brief Task
 */
typedef struct vsk_Task vsk_Task_t;

/**
 *  @brief Task operation
 */
typedef void (*vsk_Task_Operation_t)(void * const obj);

#include "ctb_DList.h"
#include "vsk_Task.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Task class
 */
struct vsk_Task_Class {
    ctb_DList_t              tasks;   /**< List of registered tasks */
    vsk_Task_Class_OnStart_t onStart; /**< Called on task scheduler start */
    vsk_Task_Class_OnIdle_t  onIdle;  /**< Called when the system is idle */
};

/**
 * @brief Task state
 */
typedef enum {
    vsk_Task_State_suspended, /**< Task is suspended */
    vsk_Task_State_ready,     /**< Task is ready */
    vsk_Task_State_running    /**< Task is running */
} vsk_Task_State_t;

/**
 * @brief Task
 */
struct vsk_Task {
    vsk_Task_Class_t *   cls;                 /**< Task class reference */
    ctb_DNode_t          node;                /**< Node to allow task to be added to a list */
    vsk_Task_Operation_t operation;           /**< Task operation */
    void *               obj;                 /**< Object reference to pass to the callback (can be NULL) */
    vsk_Task_State_t     state;               /**< Task state */
    uint32_t             lastStartTimeMillis; /**< Last start time in milliseconds */
    uint32_t             maxRunTimeMillis;    /**< Maximum run time in milliseconds */
    uint32_t             minPeriodMillis;     /**< Minimum period in milliseconds */
    uint32_t             cpuLoad;             /**< CPU load in percent */
};

/**
 * @brief Task class instance
 */
extern vsk_Task_Class_t vsk_Task_Class;

/**
 * @brief Initializes the Task class
 *
 * @param cls Task class reference
 * @param onStart On start callback
 * @param onIdle On idle callback
 * @return Initialized Task class reference
 */
vsk_Task_Class_t * vsk_Task_Class_init(
    vsk_Task_Class_t * const       cls,
    vsk_Task_Class_OnStart_t const onStart,
    vsk_Task_Class_OnIdle_t const  onIdle
);

/**
 * @brief Starts the scheduler
 *
 * @param cls Task class reference
 */
void vsk_Task_Class_startScheduler(vsk_Task_Class_t * const cls);

/**
 * @brief Initializes a task
 *
 * @param self Task reference
 * @param operation Task operation
 * @param obj Object reference to pass to the callback (can be NULL)
 * @return Initialized Task reference
 */
vsk_Task_t * vsk_Task_init(
    vsk_Task_t * const         self,
    vsk_Task_Operation_t const operation,
    void * const               obj
);

/**
 * @brief Activates a task
 *
 * @param self Task reference
 */
void vsk_Task_activate(vsk_Task_t * const self);

/**
 * @brief Suspends a task
 *
 * @param self Task reference
 */
void vsk_Task_suspend(vsk_Task_t * const self);

/** @} */
#endif // VSK_TASK_H
