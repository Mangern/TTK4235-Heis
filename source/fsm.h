/**
 * @file
 * @brief Module responsible for updating FSM state based on system events.
 */
#ifndef FSM_H
#define FSM_H

#include "types.h"

/**
 * @brief Poll events and update FSM state accordingly.
 *
 * @details Should **only** modify system->state except if absolutely necessary.
 *
 * @param[in,out] system Elevator state.
 */
void fsm_tick(system_t* system);

#endif // FSM_H
