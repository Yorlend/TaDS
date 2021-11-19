#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>
#include <time.h>

#ifdef _MSC_VER
    #include <time.h>
    #include <Windows.h>
    #include <intrin.h>
#else
    #include <sys/time.h>
    #include <x86intrin.h>
#endif

#define TIMER_BEGIN                            \
    __timer_clock = clock();                   \
    gettimeofday(&__timer_tv_1, NULL);         \
    __timer_ticks = __rdtsc();                 \

#define TIMER_END                              \
    __timer_ticks = __rdtsc() - __timer_ticks; \
    gettimeofday(&__timer_tv_2, NULL);         \
    __timer_clock = clock() - __timer_clock;   \
    __timer_real = 1e6 * (__timer_tv_2.tv_sec - __timer_tv_1.tv_sec) + __timer_tv_2.tv_usec - __timer_tv_1.tv_usec;

#define TIMER_TICKS         __timer_ticks
#define TIMER_CLOCKS        __timer_clock
#define TIMER_NANOSECONDS   (long double)(__timer_ticks / (1e3 / __timer_cpu_freq))
#define TIMER_MICROSECONDS  __timer_real
#define TIMER_MILISECONDS   (__timer_real / 1e3)
#define TIMER_SECONDS       (__timer_real / 1e6)

extern struct timeval __timer_tv_1, __timer_tv_2;
extern unsigned long long __timer_real;
extern unsigned long long __timer_ticks;
extern clock_t __timer_clock;

extern double __timer_cpu_freq;

void calc_cpu_freq(void);

#endif /* __TIMER_H__ */
