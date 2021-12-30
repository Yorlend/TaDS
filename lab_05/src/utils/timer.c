#include <stdio.h>
#include <string.h>
#include "utils/timer.h"

struct timeval __timer_tv_1, __timer_tv_2;
unsigned long long __timer_real;
unsigned long long __timer_ticks;
clock_t __timer_clock;

double __timer_cpu_freq;

void calc_cpu_freq(void)
{
    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
    char arg[256];

    int cpu_counter = 0;
    __timer_cpu_freq = 0;
    char *endptr = NULL;

    while(fgets(arg, 256, cpuinfo) != NULL)
    {
        if (strstr(arg, "cpu MHz") == arg)
        {
            __timer_cpu_freq += strtod(strstr(arg, ":") + 2, &endptr);
            cpu_counter++;
        }
    }

    __timer_cpu_freq /= cpu_counter;
    fclose(cpuinfo);
}
