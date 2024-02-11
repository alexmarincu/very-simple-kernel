/*----------------------------------------------------------------------------*/
#include "vsk_Time.h"
/*----------------------------------------------------------------------------*/
vsk_Time * vsk_Time_(void) {
    static vsk_Time self;
    return &self;
}
/*----------------------------------------------------------------------------*/
vsk_Time * vsk_Time_init(
    vsk_Time * const self, uint16_t const tickPeriodMillis
) {
    self->_tickPeriodMillis = tickPeriodMillis;
    self->_millisCount = -tickPeriodMillis;
    self->_opTimeSeconds = 0;
    return self;
}
/*----------------------------------------------------------------------------*/
void vsk_Time_onSysTick(vsk_Time * const self) {
    self->_millisCount += self->_tickPeriodMillis;
    uint16_t const millisInSecond = 1000;
    if (self->_millisCount % millisInSecond == 0) {
        self->_opTimeSeconds++;
    }
}
/*----------------------------------------------------------------------------*/
uint32_t vsk_Time_getMillisCount(vsk_Time * const self) {
    return self->_millisCount;
}
/*----------------------------------------------------------------------------*/
uint32_t vsk_Time_getOpTimeSeconds(vsk_Time * const self) {
    return self->_opTimeSeconds;
}
/*----------------------------------------------------------------------------*/
uint16_t vsk_Time_getTickPeriodMillis(vsk_Time * const self) {
    return self->_tickPeriodMillis;
}
