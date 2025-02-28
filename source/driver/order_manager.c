#include "order_manager.h"
#include "floor_tracker.h"
#include "door_manager.h"
#include "elevio.h"
#include <stdio.h>
#include <stdbool.h>

static bool orders[N_FLOORS][N_BUTTONS] = {false};

void order_manager_init() {
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            orders[f][b] = false;
        }
    }
    printf("Order_manager initialisert.\n");
}

void update_order_manager() {
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            if (elevio_callButton(f, b) && !orders[f][b]) {  // Unngå duplikate ordre
                orders[f][b] = true;
                printf("ordre registrert for %d, etg  %d\n", f, b);
            }
        }
    }
    process_orders();
}

void process_orders() {
    int current_floor = get_current_floor();
    MotorDirection current_direction = get_current_direction();

    if (current_floor == -1) {
        printf("Feil: Ingen gyldig etasje funnet\n");
        return;
    }

    printf("Prossererer orde...  Nåværende etasje: %d, Retning: %d\n", current_floor, current_direction);

    // Håndter dør hvis den er åpen
    if (is_door_open()) {
        handle_door();
        return;
    }

    // Sjekk om vi skal stoppe i nåværende etasje (kun hvis bestillingen er i riktig retning Eller om d er noen i cabb)
    if ((orders[current_floor][BUTTON_CAB]) ||
        (current_direction == DIRN_UP && orders[current_floor][BUTTON_HALL_UP]) ||  
        (current_direction == DIRN_DOWN && orders[current_floor][BUTTON_HALL_DOWN])) {

        printf("Stopp heisen og åpne døren i etasje %d\n", current_floor);
        set_motor_direction(DIRN_STOP);
        open_door();
        clear_orders_at_floor(current_floor);
        return;
    }

    // Finn høyeste og laveste bestilling
    int highest_order = -1;
    int lowest_order = -1;
    for (int f = 0; f < N_FLOORS; f++) {
        if (orders[f][BUTTON_HALL_UP] || orders[f][BUTTON_HALL_DOWN] || orders[f][BUTTON_CAB]) {
            if (lowest_order == -1) lowest_order = f;
            highest_order = f;
        }
    }

    // Hvis det ikke er noen bestillinger igjen, gå ned til 1 etasje
    if (highest_order == -1) {
        printf("Ingen ordre igjen. kjører ned til 1. etasje.\n");
        floor_tracker_init();
        //set_motor_direction(DIRN_STOP);
        return;
    }

    // Behold retningen opp til høyeste ordre, ned til laveste ordre
    if (current_direction == DIRN_UP) {
        if (current_floor < highest_order) {
            printf("Kjører opp mot etasje %d\n", highest_order);
            set_motor_direction(DIRN_UP);
        } else {
            printf("Øverste bestilling nådd. Bytter retning.\n");
            set_motor_direction(DIRN_DOWN);
        }
    } else if (current_direction == DIRN_DOWN) {
        if (current_floor > lowest_order) {
            printf("Kjører ned mot etasje %d\n", lowest_order);
            set_motor_direction(DIRN_DOWN);
        } else {
            printf("Nederste bestilling nådd. Bytter retning.\n");
            set_motor_direction(DIRN_UP);
        }
    } else { 
        // Heisen er i ro, finnr nærmeste bestilling og kjør dit
        if (current_floor < highest_order) {
            set_motor_direction(DIRN_UP);
        } else {
            set_motor_direction(DIRN_DOWN);
        }
    }
}

void clear_orders_at_floor(int floor) {
    for (int b = 0; b < N_BUTTONS; b++) {
        orders[floor][b] = false;
    }
    printf("Ordre for etg er fjernet %d\n", floor);
}

bool has_orders() {
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            if (orders[f][b]) {
                return true;
            }
        }
    }
    return false;
}