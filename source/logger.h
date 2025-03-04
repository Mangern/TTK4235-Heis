/**
 * @file
 * @brief Module responsible for logging during execution.
 */
#ifndef LOGGER_H
#define LOGGER_H

#include "types.h"

/**
 * @brief Log relevant system state.
 *
 * @param[in,out] system Elevator state.
 */
void logger_info(system_t* system);

#endif // LOGGER_H
