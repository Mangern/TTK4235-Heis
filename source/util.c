#include "util.h"

#include <stdlib.h>
#include <sys/time.h>

unsigned long timeval_udiff(struct timeval start, struct timeval end) {
    // Trying to make it robust against overflows.
    unsigned long sec_diff = end.tv_sec - start.tv_sec;
    unsigned long usec_diff = llabs(end.tv_usec - start.tv_usec);
    unsigned long tot = sec_diff * GIGA + usec_diff;
    if (start.tv_usec > end.tv_usec)
        tot -= GIGA;
    return tot;
}
