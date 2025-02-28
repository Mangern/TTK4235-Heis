#include "action.h"
#include "driver/elevio.h"
#include "types.h"
#include "order.h"
#include "util.h"
#include <assert.h>
#include <stddef.h>
#include <sys/time.h>

void set_motor_dir(system_t* system, MotorDirection dir) {
    system->dir = dir;
    elevio_motorDirection(dir);
}

void update_lights(system_t* system) {
    if (system->floor != -1) {
        // FAT L3, L4, L5
        elevio_floorIndicator(system->floor);
    }

    // FAT L1, L2
    for (int floor = 0; floor < N_FLOORS; ++floor) {
        for (int button = 0; button < N_BUTTONS; ++button) {
            elevio_buttonLamp(floor, button, system->order_table[floor][button]);
        }
    }

    // FAT L6
    if (system->state == STOP || system->state == STOP_AT_FLOOR) {
        elevio_stopLamp(1);
    } else {
        elevio_stopLamp(0);
    }
}

void action_tick(system_t* system) {
    switch (system->state) {
        case INIT:
        {
            // FAT O3: Can always go down
            set_motor_dir(system, DIRN_DOWN);
            system->goal_dir = DIRN_DOWN;
        }
        break;
        case MOVING:
        {
            if (system->goal_floor == system->floor) {
            
                // Try to keep moving if between floors
                if (system->floor_status != AT_VALID) {
                    if (system->floor_status == ABOVE_VALID) {
                        set_motor_dir(system, DIRN_DOWN);
                        system->goal_dir = DIRN_DOWN;
                    } else if (system->floor_status == BELOW_VALID) {
                        set_motor_dir(system, DIRN_UP);
                        system->goal_dir = DIRN_UP;
                    }
                } else {
                    set_motor_dir(system, DIRN_STOP);
                }
            } else if (system->goal_floor > system->floor) {
                set_motor_dir(system, DIRN_UP);
                system->goal_dir = DIRN_UP;
            } else if (system->goal_floor < system->floor) {
                set_motor_dir(system, DIRN_DOWN);
                system->goal_dir = DIRN_DOWN;
            } 
            
        }
        break;
        case IDLE:
        {
            set_motor_dir(system, DIRN_STOP);
            system->goal_dir = DIRN_STOP;
        }
        break;
        case DOOR_OPEN:
        {
            // S1: Never move if door is open
            set_motor_dir(system, DIRN_STOP);
            elevio_doorOpenLamp(1);
        }
        break;
        case DOOR_CLOSE:
        {
            elevio_doorOpenLamp(0);
            // FAT H3
            order_clear_floor(system, system->floor);
        }
        break;
        case STOP:
        case STOP_AT_FLOOR:
        {
            // FAT S4
            set_motor_dir(system, DIRN_STOP);
            system->goal_dir = DIRN_STOP;
            system->goal_floor = -1;
            // FAT S5
            order_clear_all(system);

            if (system->state == STOP_AT_FLOOR) {
                gettimeofday(&system->door_open_time, NULL);
                elevio_doorOpenLamp(1);
            }
        }
        break;
    }

    update_lights(system);
}
