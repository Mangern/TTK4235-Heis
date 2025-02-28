#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdbool.h>
#include "driver/elevio.h"
#include "types.h"

void system_init(system_t* system);

void system_tick(system_t* system);

#endif // SYSTEM_H
