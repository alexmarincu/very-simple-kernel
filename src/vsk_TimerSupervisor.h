/*----------------------------------------------------------------------------*/
#ifndef VSK_TIMERSUPERVISOR_H
#define VSK_TIMERSUPERVISOR_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_TimerSupervisor vsk_TimerSupervisor;
/*----------------------------------------------------------------------------*/
#include "ctb_DList.h"
#include "vsk_Timer.h"
/*----------------------------------------------------------------------------*/
struct vsk_TimerSupervisor {
    ctb_DList_t timers;
};
/*----------------------------------------------------------------------------*/
vsk_TimerSupervisor * vsk_TimerSupervisor_(void);
vsk_TimerSupervisor * vsk_TimerSupervisor_init(
    vsk_TimerSupervisor * const self
);
void vsk_TimerSupervisor_register(
    vsk_TimerSupervisor * const self, vsk_Timer * const timer
);
void vsk_TimerSupervisor_onTick(vsk_TimerSupervisor * const self);
#endif // VSK_TIMERSUPERVISOR_H
