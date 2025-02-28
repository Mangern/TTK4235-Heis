#ifndef UTIL_H
#define UTIL_H

#include <sys/time.h>

#define GIGA 1000000000ULL

/*
 * Return the number of nanoseconds between start and end
 */
unsigned long timeval_udiff(struct timeval start, struct timeval end);

#endif // UTIL_H
