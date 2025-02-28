#pragma once

#include <stdbool.h>

void order_manager_init();
void update_order_manager();
void process_orders();
void clear_orders_at_floor(int floor);
bool has_orders();
