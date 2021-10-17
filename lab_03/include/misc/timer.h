#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

#ifdef _MSC_VER
    #include <time.h>
    #include <Windows.h>
    #include <intrin.h>
#else
    #include <sys/time.h>
    #include <x86intrin.h>
#endif

#define TIMER_BEGIN                            \
    gettimeofday(&__timer_tv_1, NULL);         \
    __timer_ticks = __rdtsc();

#define TIMER_END                              \
    __timer_ticks = __rdtsc() - __timer_ticks; \
    gettimeofday(&__timer_tv_2, NULL);         \
    __timer_real = 1e6 * (__timer_tv_2.tv_sec - __timer_tv_1.tv_sec) + __timer_tv_2.tv_usec - __timer_tv_1.tv_usec;

#define TIMER_TICKS         __timer_ticks
#define TIMER_NANOSECONDS   __timer_real
#define TIMER_MILISECONDS   (__timer_real / 1e3)
#define TIMER_SECONDS       (__timer_real / 1e6) 


static struct timeval __timer_tv_1, __timer_tv_2;
static unsigned long long __timer_real;
static unsigned long long __timer_ticks;

#endif /* __TIMER_H__ */
