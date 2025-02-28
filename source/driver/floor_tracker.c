#include "floor_tracker.h"
#include "elevio.h"
#include <stdio.h>

static int current_floor = -1;
static MotorDirection current_direction = DIRN_STOP;

void floor_tracker_init() {
    current_floor = elevio_floorSensor();
    current_direction = DIRN_STOP;
    printf("Floor tracker initialisert ved etg %d\n", current_floor);

    // Hvis heisen ikke er i 1. etasje, kjør ned
    if (current_floor != 0) {
        printf("Heisen er ikke i 1. etasje. Kjører ned...\n");
        set_motor_direction(DIRN_DOWN);

        while (elevio_floorSensor() != 0) {
            update_floor_tracker();
        }

        // Stopper motor når den når 1. etasje
        set_motor_direction(DIRN_STOP);
        printf("Heisen har nådd 1. etasje og er klar.\n");
    } else {
        printf("Heisen er allerede i 1. etasje.\n");
    }
}

void update_floor_tracker() {
    int new_floor = elevio_floorSensor();
    if (new_floor != -1 && new_floor != current_floor) {
        current_floor = new_floor;
        elevio_floorIndicator(current_floor);
        printf("Heisen er nå i etg %d\n", current_floor);
    }
}

void set_motor_direction(MotorDirection dir) {
    current_direction = dir;
    elevio_motorDirection(dir);
    printf("Motorretning satt til %d\n", dir);
}

int get_current_floor() {
    return current_floor;
}

MotorDirection get_current_direction() {
    return current_direction;
}
