/**
 * @file
 * @brief Module containing general helper functions.
 */
#ifndef UTIL_H
#define UTIL_H

#include <sys/time.h>

#define GIGA 1000000000ULL

/*
 * @brief Calculate time difference in nanoseconds.
 *
 * @param[in] start Start of time interval.
 * @param[in] end   End of time interval.
 *
 * @return the number of nanoseconds between start and end
 */
unsigned long timeval_udiff(struct timeval start, struct timeval end);

#endif // UTIL_H
