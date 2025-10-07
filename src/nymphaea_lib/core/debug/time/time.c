#include"pch.h"
#include"time.h"

double np_get_time() {
    LARGE_INTEGER counter, frequency;
    // get frequency
    QueryPerformanceFrequency(&frequency);
    // get the actual counter
    QueryPerformanceCounter(&counter);
    // return value in mili-seconds
    //return ((double)counter.QuadPart - g_np_time_context.counter_begin) * 1000.0 / g_np_time_context.frequency;
    return (double)counter.QuadPart * 1000.0 / (double)frequency.QuadPart;
}