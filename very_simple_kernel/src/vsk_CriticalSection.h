/*----------------------------------------------------------------------------*/
#ifndef VSK_CRITICALSECTION_H
#define VSK_CRITICALSECTION_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_CriticalSection vsk_CriticalSection;
/*----------------------------------------------------------------------------*/
#include <stdint.h>
/*----------------------------------------------------------------------------*/
typedef void (*vsk_CriticalSectionOnEnter)(void);
typedef void (*vsk_CriticalSectionOnExit)(void);
/*----------------------------------------------------------------------------*/
struct vsk_CriticalSection {
    vsk_CriticalSectionOnEnter _onEnter;
    vsk_CriticalSectionOnExit _onExit;
    uint8_t volatile _nestingLevels;
};
/*----------------------------------------------------------------------------*/
vsk_CriticalSection * vsk_CriticalSection_(void);
vsk_CriticalSection * vsk_CriticalSection_init(
    vsk_CriticalSection * const self,
    vsk_CriticalSectionOnEnter const onEnter,
    vsk_CriticalSectionOnExit const onExit
);
void vsk_CriticalSection_enter(vsk_CriticalSection * const self);
void vsk_CriticalSection_exit(vsk_CriticalSection * const self);
#endif // VSK_CRITICALSECTION_H
