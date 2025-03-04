/**
 * @file
 * @brief Module responsible for collecting orders and calculating the next floor to go to in a given moment.
 */
#ifndef ORDER_H
#define ORDER_H

#include "system.h"

/**
 * @brief Poll for new orders.
 *
 * @param[in,out] system Elevator state.
 */
void order_tick(system_t* system);

/**
 * @brief Fetch the next order. 
 *
 * @details If the elevator has a movement direction it will ignore all orders for the oppsite direction until finished with the current direction. 
 * Will always return the closest ordered floor in the movement direction. 'Movement direction' is here defined as goal_dir.
 *
 * @param[in,out] system Elevator state
 *
 * @return The floor to go to. -1 if no order exists.
 */
int order_get_next(system_t* system);

/**
 * @brief Clear all orders on a floor.
 *
 * @param[in,out] system Elevator state
 */
void order_clear_floor(system_t *system, int floor);

/**
 * @brief Clear all orders.
 *
 * @param[in,out] system Elevator state
 */
void order_clear_all(system_t *system);

#endif // ORDER_H
