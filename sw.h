#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <time.h>

//MACRO OPTIONS ======================================================================

//Should print functions be enabled? (Comment to disable)
#define SW_PRINT_FUNCTIONS

//Should the minute functions be enabled? (Uncomment to enable)
// #define SW_MINUTE_FUNCTIONS

//Should memory functions be enabled (Comment to disable)
#define SW_MEMORY

//Printing time format, we use doubles, so make sure to use a %f
#define PRINT_US_FORMAT "%.0fus\n"
#define PRINT_MS_FORMAT "%.4fms\n"
#define PRINT_S_FORMAT "%.4fs\n"
#define PRINT_MIN_FORMAT "%.2fmins\n"

//Printing sizes format
#define PRINT_B_FORMAT "%.0fB\n"
#define PRINT_KB_FORMAT "%.2fKB\n"
#define PRINT_MB_FORMAT "%.5fMB\n"
#define PRINT_GB_FORMAT "%.5fGB\n"

//MACRO BACKEND ======================================================================

//Include stdio.h if we are enabling print functions
#ifdef SW_PRINT_FUNCTIONS

#include <stdio.h>

#endif //SW_PRINT_FUNCTIONS

#ifdef SW_MEMORY
#ifdef __WIN32

#include <windows.h>
#include <psapi.h>
#include <math.h>

#elif __linux__

#include <sys/resource.h>

#endif


#endif //SW_MEMORY

//MICROSECOND FUNCTIONS ======================================================================

/// Start the microsecond timer, returns the start time
/// @return The current timeofday in microseconds, use this as the prev arg for `sw_stop_us()`
inline double sw_start_us() {
    struct timespec a;
    clock_gettime(CLOCK_MONOTONIC, &a);
    return a.tv_nsec / 1000.0 + (double) a.tv_sec * 1000.0 * 1000.0;
}

/// Stop the microsecond timer
/// @param prev The start time from `inline double sw_start_us()`
/// @return The time between stop and start in microseconds
inline double sw_stop_us(const double prev) {
    return (sw_start_us() - prev);
}

#ifdef SW_PRINT_FUNCTIONS

/// Prints the elapsed seconds since prev in microseconds
/// @param prev The start time from `inline double sw_start_us()`
inline void sw_print_us(const double prev) {
    printf(PRINT_US_FORMAT, fabs(sw_stop_us(prev)));
}

#endif //SW_PRINT_FUNCTIONS

//MILLISECOND FUNCTIONS ======================================================================

/// Start the millisecond timer, returns the start time.
/// @return The current timeofday in milliseconds, use this as the prev arg for `sw_stop_ms()'
inline double sw_start_ms() {
    return sw_start_us() / 1000.0;
}

/// Stop the millisecond timer
/// @param prev The start time from `inline double sw_start_ms()`
/// @return The time between stop and start in milliseconds
inline double sw_stop_ms(const double prev) {
    return (sw_start_ms() - prev);
}

#ifdef SW_PRINT_FUNCTIONS

/// Prints the elapsed seconds since prev in miliseconds
/// @param prev The start time from `inline double sw_start_ms()`
inline void sw_print_ms(const double prev) {
    printf(PRINT_MS_FORMAT, sw_stop_ms(prev));
}

#endif //SW_PRINT_FUNCTIONS

//SECOND FUNCTIONS ======================================================================

/// Start the second timer, returns the start time.
/// @return The current timeofday in seconds, use this as the prev arg for `sw_stop_s`
inline double sw_start_s() {
    return sw_start_ms() / 1000.0;
}

/// Stop the second timer
/// @param prev The start time from `inline double sw_start_s()`
/// @return The time between stop and start in seconds
inline double sw_stop_s(const double prev) {
    return (sw_start_s() - prev);
}

#ifdef SW_PRINT_FUNCTIONS

/// Prints the elapsed seconds since prev in seconds
/// @param prev The start time from `inline double sw_start_s()`
inline void sw_print_s(const double prev) {
    printf(PRINT_S_FORMAT, sw_stop_s(prev));
}

#endif //SW_PRINT_FUNCTIONS


//MINUTE FUNCTIONS ======================================================================

#ifdef SW_MINUTE_FUNCTIONS
/// Start the second timer, returns the start time.
/// @return The current timeofday in seconds, use this as the prev arg for `sw_stop_min`
inline double sw_start_min()
{
    return sw_start_s() / 60;
}

/// Stop the second timer
/// @param prev The start time from `inline double sw_start_min()`
/// @return The time between stop and start in minutes
inline double sw_stop_min(const double prev)
{
    return (sw_start_min() - prev);
}

#ifdef SW_PRINT_FUNCTIONS
/// Prints the elapsed seconds since prev in mins
/// @param prev The start time from `inline double sw_start_min()`
inline void sw_print_min(const double prev)
{
    printf(PRINT_MIN_FORMAT, sw_stop_min(prev));
}
#endif //SW_PRINT_FUNCTIONS

#endif //SW_MINUTE_FUNCTIONS


#ifdef SW_MEMORY

/// Get the current memory usage of this application
/// @return The size of memory in bytes
inline double sw_memory_size_b() {
#ifdef __WIN32
    const HANDLE hproc = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(hproc, (PPROCESS_MEMORY_COUNTERS) &pmc, sizeof(pmc))) {
        CloseHandle(hproc);
        //In bytes?
        return pmc.WorkingSetSize;
    }
    CloseHandle(hproc);
    return -1;

#elif __linux__
    struct rusage use;
    getrusage(RUSAGE_SELF, &use);
    return use.ru_maxrss * 1000.0;
#endif
}

/// Gets and prints the memory usage in bytes
inline void sw_memory_print_b() {
    printf(PRINT_B_FORMAT, sw_memory_size_b());
}

/// Get the current memory usage of this application
/// @return The size of memory in kilobytes
inline double sw_memory_size_kb() {
    return sw_memory_size_b() / 1000.0;
}

/// Gets and prints the memory usage in kilobytes
inline void sw_memory_print_kb() {
    printf(PRINT_KB_FORMAT, sw_memory_size_kb());
}

/// Get the current memory usage of this application
/// @return The size of memory in megabytes
inline double sw_memory_size_mb() {
    return sw_memory_size_kb() / 1000.0;
}

/// Gets and prints the memory usage in megabytes
inline void sw_memory_print_mb() {
    printf(PRINT_MB_FORMAT, sw_memory_size_mb());
}

/// Get the current memory usage of this application
/// @return The size of memory in gigabytes
inline double sw_memory_size_gb() {
    return sw_memory_size_mb() / 1000.0;
}

/// Gets and prints the memory usage in gigabytes
inline void sw_memory_print_gb() {
    printf(PRINT_GB_FORMAT, sw_memory_size_gb());
}

/// Prints the memory usage with the correct formatting in the ideal size.
/// i.e. doesnt print 1000 bytes as "1000b" but as "1mb"
inline void sw_memory_print_auto() {
    const double size = sw_memory_size_b();
    if (size < 1000) {
        printf(PRINT_B_FORMAT, size);
    } else if (size < 1000 * 1000) {
        printf(PRINT_KB_FORMAT, size / 1000.0);
    } else if (size < 1000 * 1000 * 1000) {
        printf(PRINT_MB_FORMAT, size / 1000.0 / 1000.0);
    } else {
        printf(PRINT_GB_FORMAT, size / 1000.0 / 1000.0 / 1000.0);
    }
}

#endif //SW_MEMORY

#endif //STOPWATCH_H

//
// Created by TobinC on 5/9/2024.
//
