#include "fsm.h"
#include "types.h"
#include "util.h"
#include <assert.h>
#include <stddef.h>
#include <sys/time.h>

void fsm_tick(system_t *system) {
    int stop_button_pressed = elevio_stopButton();
    switch (system->state) {
        case INIT:
        {
            // FAT O1
            if (system->floor != -1) {
                system->state = IDLE;
                system->floor_status = AT_VALID;
            }
        }
        break;
        case MOVING:
        {
            if (system->goal_floor == -1) {
                // FAT H4
                system->state = IDLE;
            } else if (system->goal_floor == system->floor && system->floor_status == AT_VALID /* FAT S2 */) {
                system->state = DOOR_OPEN;
                gettimeofday(&system->door_open_time, NULL);
            }
        }
        break;
        case IDLE:
        {
            if (system->goal_floor != -1) {
                system->state = MOVING;
            }
        }
        break;
        case DOOR_OPEN:
        {
            struct timeval curr_time;
            gettimeofday(&curr_time, NULL);
            unsigned long time_open = timeval_udiff(system->door_open_time, curr_time);

            // FAT D1, D2
            if (time_open >= 3 * GIGA) {
                system->state = DOOR_CLOSE;
            }
        }
        break;
        case DOOR_CLOSE:
        {
            if (system->goal_dir != DIRN_STOP) {
                system->state = MOVING;
            } else {
                system->state = IDLE;
            }
        }
        break;
        case STOP:
        {
            if (!stop_button_pressed) {
                // FAT S7
                system->state = IDLE;
            }
        }
        break;
        case STOP_AT_FLOOR:
        {
            if (!stop_button_pressed) {
                // FAT S7
                system->state = DOOR_OPEN;
            }
        }
        break;
    }

    if (stop_button_pressed && system->state != INIT) {
        // FAT D3
        if (elevio_floorSensor() != -1) {
            system->state = STOP_AT_FLOOR;
        } else {
            system->state = STOP;
        }
    }
}
