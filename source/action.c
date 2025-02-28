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
        elevio_floorIndicator(system->floor);
    }

    for (int floor = 0; floor < N_FLOORS; ++floor) {
        for (int button = 0; button < N_BUTTONS; ++button) {
            elevio_buttonLamp(floor, button, system->order_table[floor][button]);
        }
    }
}

void action_tick(system_t* system) {
    switch (system->state) {
        case INIT:
        {
            set_motor_dir(system, DIRN_DOWN);
            system->goal_dir = DIRN_DOWN;
        }
        break;
        case MOVING:
        {
            if (system->goal_floor == system->floor) {
                set_motor_dir(system, DIRN_STOP);
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
            // Never move if door is open
            set_motor_dir(system, DIRN_STOP);
            elevio_doorOpenLamp(1);
        }
        break;
        case DOOR_CLOSE:
        {
            elevio_doorOpenLamp(0);
            order_clear_floor(system, system->floor);
        }
        break;
        case STOP:
        {
            assert(0); // not implemented
        }
        break;
    }

    update_lights(system);
}
