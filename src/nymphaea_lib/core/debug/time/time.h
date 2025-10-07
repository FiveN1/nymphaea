#ifndef NP_TIME_H
#define NP_TIME_H

/*
* time.h
* - includes all functions fo measuring time.
* - shoud not be platform specific!
* 
* NOTE: timer is platform specific
* NOTE: not all windows versions support the windows timer
* https://learn.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancefrequency
*
*
*/


// get high-percision time in mili-seconds
double np_get_time();

#endif NP_TIME_H