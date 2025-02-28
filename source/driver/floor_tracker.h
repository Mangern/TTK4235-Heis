#pragma once

#include "elevio.h"

void floor_tracker_init();
void update_floor_tracker();
void set_motor_direction(MotorDirection dir);
int get_current_floor();
MotorDirection get_current_direction();