/*----------------------------------------------------------------------------*/
#ifndef VSK_TIMER_H
#define VSK_TIMER_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_Timer vsk_Timer;
/*----------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
/*----------------------------------------------------------------------------*/
#include "../../c-tool-box/c_tool_box/src/ctb_Node.h"
/*----------------------------------------------------------------------------*/
typedef void (*vsk_TimerCallback)(void * const obj);
/*----------------------------------------------------------------------------*/
struct vsk_Timer {
    ctb_Node node;
    uint32_t delayMillis;
    uint32_t periodMillis;
    vsk_TimerCallback callback;
    void * obj;
    uint32_t volatile millisCountDown;
    bool volatile isRunning;
};
/*----------------------------------------------------------------------------*/
vsk_Timer * vsk_Timer_init(
    vsk_Timer * const self,
    uint32_t const delayMillis,
    uint32_t const periodMillis,
    vsk_TimerCallback const callback,
    void * const obj
);
void vsk_Timer_start(vsk_Timer * const self);
void vsk_Timer_stop(vsk_Timer * const self);
bool vsk_Timer_isRunning(vsk_Timer * const self);
void vsk_Timer_onTick(vsk_Timer * const self);
#endif // VSK_TIMER_H
