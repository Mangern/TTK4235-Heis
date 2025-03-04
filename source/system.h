/**
 * @file
 * @brief Module responsible for initializing state variables and calling all other modules each tick.
 */
#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdbool.h>
#include "driver/elevio.h"
#include "types.h"

/**
 * @brief Initializes the system.
 *
 * @param[in,out] system Already allocated system struct.
 */
void system_init(system_t* system);

/**
 * @brief Ticks all other modules.
 *
 * @param[in,out] system.
 */
void system_tick(system_t* system);

#endif // SYSTEM_H
