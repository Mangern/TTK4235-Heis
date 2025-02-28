#include "logger.h"
#include "driver/elevio.h"
#include "types.h"
#include <stdbool.h>
#include <stdio.h>

system_t prev_system;
bool initialized = false;

char* state_str(fsm_state_t state) {
    switch (state) {
    case INIT:
        return "INIT";
    case MOVING:
        return "MOVING";
    case IDLE:
        return "IDLE";
    case DOOR_OPEN:
        return "DOOR_OPEN";
    case DOOR_CLOSE:
        return "DOOR_CLOSE";
    case STOP:
        return "STOP";
      break;
    }
}

char* dir_str(MotorDirection dir) {
    switch (dir) {
    case DIRN_DOWN:
        return "DIRN_DOWN";
    case DIRN_STOP:
        return "DIRN_STOP";
    case DIRN_UP:
        return "DIRN_UP";
      break;
    }
}

void logger_info(system_t *system) {
    if (!initialized) {

        printf("System initialized\n");
        printf("State: %s\n", state_str(system->state));
        printf("Dir: %s\n", dir_str(system->dir));
        printf("Goal Dir: %s\n", dir_str(system->goal_dir));
        printf("Goal Floor: %d\n", system->goal_floor);
        printf("\n");
        initialized = true;
    } else {
        if (prev_system.state != system->state) {
            printf("New State: %s\n", state_str(system->state));
        }

        if (prev_system.dir != system->dir) {
            printf("New Dir: %s\n", dir_str(system->dir));
        }

        if (prev_system.goal_dir != system->goal_dir) {
            printf("New Goal Dir: %s\n", dir_str(system->goal_dir));
        }

        if (prev_system.goal_floor != system->goal_floor) {
            printf("New Goal Floor: %d\n", system->goal_floor);
        }
    }
    prev_system = *system;
}
