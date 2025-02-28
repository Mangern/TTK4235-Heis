#ifndef ORDER_H
#define ORDER_H

#include "system.h"

/**
 * @brief Poll for new orders.
 */
void order_tick(system_t* system);

/**
 * @brief Fetch the next order. 
 *
 * @return The floor to go to. -1 if no order exists.
 */
int order_get_next(system_t* system);

void order_clear_floor(system_t *system, int floor);

#endif // ORDER_H
