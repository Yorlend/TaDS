#include <time.h>
#include "misc/timer.h"


static clock_t __begin;

void timer_start()
{
    __begin = clock();
}

long timer_end()
{
    clock_t end = clock();

    return end - __begin;
}
