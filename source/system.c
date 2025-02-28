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

    for (int i = 0; i < N_FLOORS; ++i) {
        memset(system->order_table, 0, N_BUTTONS * sizeof(bool));
    }
}

void update_sensors(system_t *system) {
    int floor_sensor = elevio_floorSensor();

    if (floor_sensor >= 0) {
        system->floor = floor_sensor;
    }

    // FAT D4
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
