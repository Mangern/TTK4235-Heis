#include "fsm.h"
#include "types.h"
#include "util.h"
#include <assert.h>
#include <stddef.h>
#include <sys/time.h>

void fsm_tick(system_t *system) {
    switch (system->state) {
        case INIT:
        {
            if (system->floor != -1) {
                system->state = IDLE;
            }
        }
        break;
        case MOVING:
        {
            if (system->goal_floor == -1) {
                system->state = IDLE;
            } else if (system->goal_floor == system->floor) {
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

            // FAT D1
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
            assert(0); // not implemented
        }
        break;
    }
}
