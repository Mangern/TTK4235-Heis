#include "door_manager.h"
#include "elevio.h"
#include <time.h>
#include <stdbool.h>

static bool door_open = false;
static struct timespec door_timer;

void open_door() {
    elevio_doorOpenLamp(1);
    clock_gettime(CLOCK_MONOTONIC, &door_timer);
    door_open = true;
}

void close_door() {
    elevio_doorOpenLamp(0);
    door_open = false;
}

bool is_door_open() {
    return door_open;
}

void handle_door() {
    if (door_open) {
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        double elapsed_time = (now.tv_sec - door_timer.tv_sec) + (now.tv_nsec - door_timer.tv_nsec) / 1.0e9;
        
        // Vent i minst 3 sekunder, sjekker obsturksjon
        if (elapsed_time >= 3.0) {
            if (!elevio_obstruction()) {
                close_door();
            } else {
                // Reset timer hvis obstruksjon er tilstede
                clock_gettime(CLOCK_MONOTONIC, &door_timer);
            }
        }
    }
}