#include "vsk_Time.h"

vsk_Time_t vsk_Time;

vsk_Time_t * vsk_Time_init(
    vsk_Time_t * const self, uint16_t const tickPeriodMillis
) {
    self->tickPeriodMillis = tickPeriodMillis;
    self->millisCount      = -tickPeriodMillis;
    self->opTimeSeconds    = 0;
    return self;
}

void vsk_Time_onTick(vsk_Time_t * const self) {
    self->millisCount += self->tickPeriodMillis;
    uint16_t const millisInSecond = 1000;
    if (self->millisCount % millisInSecond == 0) {
        self->opTimeSeconds++;
    }
}

uint32_t vsk_Time_getMillisCount(vsk_Time_t * const self) {
    (void)self;
    return self->millisCount;
}

// cppcheck-suppress unusedFunction // API function
uint32_t vsk_Time_getOpTimeSeconds(vsk_Time_t * const self) {
    (void)self;
    return self->opTimeSeconds;
}

uint16_t vsk_Time_getTickPeriodMillis(vsk_Time_t * const self) {
    (void)self;
    return self->tickPeriodMillis;
}
