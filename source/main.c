/**
 * @file
 * @brief The entry point of the Elevator application.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "driver/elevio.h"
#include "system.h"

int main(){
    elevio_init();
    
    system_t system;
    system_init(&system);

    while(!system.should_stop){
        system_tick(&system);
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}

