#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/floor_tracker.h"
#include "driver/order_manager.h"
#include "driver/light_manager.h"
#include "driver/door_manager.h"


int main() {
    elevio_init();
    floor_tracker_init();
    order_manager_init();

    printf("=== Elevator Control Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_STOP); //starter i ro

    while (1) {
        update_floor_tracker();
        update_order_manager();
        update_lights();

        if (elevio_stopButton()) {
            printf("\nStoppet!\n");
            elevio_motorDirection(DIRN_STOP);
            elevio_stopLamp(1);
            nanosleep(&(struct timespec){0, 3*1000*1000*1000}, NULL); // Vent 3 sek før avslutning
            break;
        }

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL); // 20ms pause mellom oppdateringer
    }

    return 0;
}