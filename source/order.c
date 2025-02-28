#include "order.h"
#include "driver/elevio.h"

#include <stddef.h>
#include <stdbool.h>

void order_tick(system_t* system) {
    if (system == NULL) return;
    // FAT O2
    if (system->floor == -1) return;

    for (size_t floor = 0; floor < N_FLOORS; ++floor) {
        for (size_t button = 0; button < N_BUTTONS; ++button) {
            if (elevio_callButton(floor, button)) {
                system->order_table[floor][button] = true;
            }
        }
    }

    system->goal_floor = order_get_next(system);
}

int order_get_next(system_t* system) {
    // Undefined state, don't do orders (FAT O2)
    if (system->floor == -1) return -1;

    if (system->goal_floor != -1) {
        switch(system->goal_dir) {
            case DIRN_UP:
            {
                for (int floor = system->floor; floor < system->goal_floor; ++floor) {
                    // Don't take orders in reverse direction (FAT H2)
                    if (system->order_table[floor][BUTTON_HALL_UP] || system->order_table[floor][BUTTON_CAB])
                        return floor;
                }

                for (int floor = system->goal_floor; floor < N_FLOORS; ++floor) {
                    for (int button = 0; button < N_BUTTONS; ++button) {
                        if (system->order_table[floor][button])
                            return floor;
                    }
                }
            }
            break;
            case DIRN_DOWN:
            {
                for (int floor = system->floor; floor > system->goal_floor; --floor) {
                    // Don't take orders in reverse direction (FAT H2)
                    if (system->order_table[floor][BUTTON_HALL_DOWN] || system->order_table[floor][BUTTON_CAB])
                        return floor;
                }

                for (int floor = system->goal_floor; floor >= 0; --floor) {
                    for (int button = 0; button < N_BUTTONS; ++button) {
                        if (system->order_table[floor][button])
                            return floor;
                    }
                }
            }
            break;

            default:
                break;
        }
    }

    // Find any order
    for (int floor = 0; floor < N_FLOORS; ++floor) {
        for (int button = 0; button < N_BUTTONS; ++button) {
            if (system->order_table[floor][button])
                return floor;
        }
    }

    return -1;
}

void order_clear_floor(system_t *system, int floor) {
    for (int button = 0; button < N_BUTTONS; ++button) {
        system->order_table[floor][button] = false;
    }
}
