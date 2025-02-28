#ifndef TYPES_H
#define TYPES_H

#include <bits/types/struct_timeval.h>
#include <stdbool.h>
#include "driver/elevio.h"

typedef enum {
    UNKNOWN,
    ABOVE_VALID,
    BELOW_VALID,
    AT_VALID
} floor_status_t;

typedef enum {
    INIT,
    MOVING,
    IDLE,
    DOOR_OPEN,
    DOOR_CLOSE,
    STOP,
    STOP_AT_FLOOR
} fsm_state_t;


typedef struct {
    // Last valid floor
    int floor;
    int goal_floor;
    MotorDirection dir;
    MotorDirection goal_dir;
    fsm_state_t state;
    floor_status_t floor_status;
    bool should_stop;
    struct timeval door_open_time;
    bool order_table[N_FLOORS][N_BUTTONS];
} system_t;

#endif // TYPES_H
