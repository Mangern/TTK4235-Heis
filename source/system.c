#include "system.h"
#include "action.h"
#include "driver/elevio.h"
#include "fsm.h"
#include "logger.h"
#include "order.h"
#include "types.h"
#include <string.h>
#include <stddef.h>
#include <sys/time.h>

void system_init(system_t *system) {
    system->state = INIT;
    system->should_stop = false;
    system->floor = -1;
    system->goal_floor = -1;
    system->goal_dir = DIRN_STOP;
    system->dir = DIRN_STOP;
    system->floor_status = UNKNOWN;

    for (int i = 0; i < N_FLOORS; ++i) {
        for (int j = 0; j < N_BUTTONS; ++j) {
            system->order_table[i][j] = false;
            elevio_buttonLamp(i, j, 0);
        }
    }
    elevio_doorOpenLamp(0);
    elevio_stopLamp(0);
    elevio_floorIndicator(0);
}

void update_sensors(system_t *system) {
    int floor_sensor = elevio_floorSensor();

    if (floor_sensor >= 0) {
        system->floor = floor_sensor;
        system->floor_status = AT_VALID;
    } else if (system->floor_status == AT_VALID) {
        if (system->dir == DIRN_UP) {
            system->floor_status = ABOVE_VALID;
        } else if (system->dir == DIRN_DOWN) {
            system->floor_status = BELOW_VALID;
        }
    }

    // FAT D4, O1
    if (system->state == DOOR_OPEN && elevio_obstruction()) {
        gettimeofday(&system->door_open_time, NULL);
    }
}

void system_tick(system_t *system) {
    logger_info(system);
    update_sensors(system);
    order_tick(system);
    fsm_tick(system);
    action_tick(system);
}
