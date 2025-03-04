/**
 * @file
 * @brief All data types and enums.
 */
#ifndef TYPES_H
#define TYPES_H

#include <bits/types/struct_timeval.h>
#include <stdbool.h>
#include "driver/elevio.h"

/**
 * @brief Status of system floor variable.
 */
typedef enum {
    UNKNOWN,      /*!< The system does not know where it is. */
    ABOVE_VALID,  /*!< The system is somewhere above the last known floor. */
    BELOW_VALID,  /*!< The system is somewhere below the last known floor. */
    AT_VALID      /*!< The system is at a floor. */
} floor_status_t;

/**
 * @brief States of finite state machine.
 */
typedef enum {
    INIT,
    MOVING,
    IDLE,
    DOOR_OPEN,
    DOOR_CLOSE,
    STOP,
    STOP_AT_FLOOR
} fsm_state_t;


/**
 * @brief Structure containing all elevator state.
 */
typedef struct {
    int floor;                                /*!< The last known valid floor. -1 during initialization. */
    int goal_floor;                           /*!< The current floor we want to go to. -1 if idle. */
    MotorDirection dir;                       /*!< The current direction we are moving. */
    MotorDirection goal_dir;                  /*!< Used for continuing movement after stopping at a floor. */
    fsm_state_t state;                        /*!< Current FSM state. */
    floor_status_t floor_status;              /*!< Additional information about elevator position relative to last valid floor. */
    bool should_stop;                         /*!< Unused variable that can be used to exit the program. */
    struct timeval door_open_time;            /*!< Variable used to record how long the door is open. */
    bool order_table[N_FLOORS][N_BUTTONS];    /*!< Table storing all recorded orders */
} system_t;

#endif // TYPES_H
