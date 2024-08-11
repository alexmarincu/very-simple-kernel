/*----------------------------------------------------------------------------*/
#ifndef VSK_TIME_H
#define VSK_TIME_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_Time vsk_Time;
/*----------------------------------------------------------------------------*/
#include <stdint.h>
/*----------------------------------------------------------------------------*/
struct vsk_Time {
    uint16_t tickPeriodMillis;
    uint32_t volatile millisCount;
    uint32_t volatile opTimeSeconds;
};
/*----------------------------------------------------------------------------*/
vsk_Time * vsk_Time_(void);
vsk_Time * vsk_Time_init(
    vsk_Time * const self, uint16_t const tickPeriodMillis
);
uint32_t vsk_Time_getMillisCount(vsk_Time * const self);
uint32_t vsk_Time_getOpTimeSeconds(vsk_Time * const self);
uint16_t vsk_Time_getTickPeriodMillis(vsk_Time * const self);
void vsk_Time_onTick(vsk_Time * const self);
#endif // VSK_TIME_H
