#ifndef PERFCNT_H_
#define PERFCNT_H_

#include <Windows.h>

class PerfCnt
{
public:
    PerfCnt(void) {
        QueryPerformanceCounter((LARGE_INTEGER*)&start);
    }
    double elapsed(void) {
        __int64 stop, freq;
        QueryPerformanceCounter((LARGE_INTEGER*)&stop);
        QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
        return (double)(stop - start)/(float)freq;
    }
private:
    __int64 start;
};

#endif