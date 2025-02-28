#include "light_manager.h"
#include "elevio.h"
#include "order_manager.h"
#include "floor_tracker.h"

static int previous_floor = -1;

void update_lights() {
    int current_floor = get_current_floor();
    if (current_floor != -1) {
        elevio_floorIndicator(current_floor);
        previous_floor = current_floor;
    }
    
    // Hvis heisen er mellom etasjer, behold lys fra forrige etasje
    if (current_floor == -1 && previous_floor != -1) {
        elevio_floorIndicator(previous_floor);
    }
    
    // Oppdater bestillingslys basert på aktive ordrer
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            elevio_buttonLamp(f, b, elevio_callButton(f, b));
        }
    }
}

void clear_order_lights(int floor) {
    for (int b = 0; b < N_BUTTONS; b++) {
        elevio_buttonLamp(floor, b, 0);
    }
}

void set_door_light(bool state) {
    elevio_doorOpenLamp(state);
}

void set_stop_light(bool state) {
    elevio_stopLamp(state);
}