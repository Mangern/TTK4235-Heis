/**
 * @file
 * @brief Module responsible for interacting with the physical elevator. This includes lights, door and motors.
 */
#ifndef ACTION_H
#define ACTION_H

#include "system.h"

/**
 * @brief Update actuators based on current state.
 *
 * @param[in,out] system Elevator state.
 */
void action_tick(system_t* system);

#endif // ACTION_H
