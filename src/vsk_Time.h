/**
 * @file
 */
#ifndef VSK_TIME_H
#define VSK_TIME_H
/**
 * @ingroup vsk
 * @defgroup vsk_Time vsk_Time
 * @{
 */

/**
 * @brief Time
 */
typedef struct vsk_Time vsk_Time_t;

#include <stdint.h>

/**
 * @brief Time
 */
struct vsk_Time {
    uint16_t tickPeriodMillis;       /**< The period at which the system ticks */
    uint32_t volatile millisCount;   /**< The number of milliseconds since the system started */
    uint32_t volatile opTimeSeconds; /**< The number of seconds since the system started */
};

/**
 * @brief Time instance
 */
extern vsk_Time_t vsk_Time;

/**
 * @brief Initializes the Time instance
 *
 * @param self Time reference
 * @param tickPeriodMillis The period at which the system ticks
 * @return Initialized Time reference
 */
vsk_Time_t * vsk_Time_init(
    vsk_Time_t * const self, uint16_t const tickPeriodMillis
);

/**
 * @brief Gets the number of milliseconds since the system started
 *
 * @param self Time reference
 * @return The number of milliseconds since the system started
 */
uint32_t vsk_Time_getMillisCount(vsk_Time_t * const self);

/**
 * @brief Gets the number of seconds since the system started
 *
 * @param self Time reference
 * @return The number of seconds since the system started
 */
uint32_t vsk_Time_getOpTimeSeconds(vsk_Time_t * const self);

/**
 * @brief Gets the configured tick period in milliseconds
 *
 * @param self Time reference
 * @return The configured tick period in milliseconds
 */
uint16_t vsk_Time_getTickPeriodMillis(vsk_Time_t * const self);

/**
 * @brief Ticks the time
 *
 * @param self Time reference
 */
void vsk_Time_onTick(vsk_Time_t * const self);

/** @} */
#endif // VSK_TIME_H
