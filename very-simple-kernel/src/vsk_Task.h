/*----------------------------------------------------------------------------*/
#ifndef VSK_TASK_H
#define VSK_TASK_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_Task vsk_Task;
/*----------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
/*----------------------------------------------------------------------------*/
#include "../../c-tool-box/c_tool_box/src/ctb_Node.h"
/*----------------------------------------------------------------------------*/
typedef void (*vsk_TaskOperation)(void * const obj);
typedef enum {
    vsk_TaskState_suspended,
    vsk_TaskState_ready,
    vsk_TaskState_running
} vsk_TaskState;
/*----------------------------------------------------------------------------*/
struct vsk_Task {
    ctb_Node node;
    vsk_TaskOperation operation;
    void * obj;
    vsk_TaskState state;
    uint32_t lastStartTimeMillis;
    uint32_t maxRunTimeMillis;
    uint32_t minPeriodMillis;
    uint32_t cpuLoad;
};
/*----------------------------------------------------------------------------*/
vsk_Task * vsk_Task_init(
    vsk_Task * const self, vsk_TaskOperation const operation, void * const obj
);
bool vsk_Task_isReady(vsk_Task * const self);
void vsk_Task_run(vsk_Task * const self);
void vsk_Task_activate(vsk_Task * const self);
void vsk_Task_suspend(vsk_Task * const self);
ctb_Node * vsk_Task_toNode(vsk_Task * const self);
#endif // VSK_TASK_H
